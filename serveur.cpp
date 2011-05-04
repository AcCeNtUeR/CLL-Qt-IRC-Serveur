#include "serveur.h"
#include "ui_serveur.h"

Serveur::Serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Serveur)
{
    ui->setupUi(this);
    m_QTcpServer = new QTcpServer();
    m_QTcpServer->listen(QHostAddress::Any,60123);
    connect(m_QTcpServer,SIGNAL(newConnection()),this,SLOT(Connection()));
}

Serveur::~Serveur()
{
    delete ui;
}

void Serveur::on_btnStart_clicked()
{
    ui->btnStart->hide();
    ui->btnCommencer->show();
}

void Serveur::on_btnCommencer_clicked()
{
    ui->btnStart->show();
    ui->btnCommencer->hide();
}

void Serveur::Connection()
{
   sockClient = m_QTcpServer->nextPendingConnection();
   QString ChatRoom = "";
   int i = 0;
   while(i < 6)
   {
       if(!tChatroom[i]->isEmpty())
       {
        ChatRoom += tChatroom[i] +"\n";
       }
     i++;
   }
   sockClient->write(ChatRoom.toAscii());

    ThreadConnect *maThreadConnect = new ThreadConnect(sockClient);
    connect(maThreadConnect,SIGNAL(siNouvelleCre(QString)),this,SLOT(NewChat(QString)));
    connect(maThreadConnect,SIGNAL(siNouvelleCon(QString)),this,SLOT(NewCon(QString)));
    connect(this,SIGNAL(siValidCre(QString)),maThreadConnect,SLOT(FonctionValidCre(QString)));
    connect(this,SIGNAL(siValidCon(QString)),maThreadConnect,SLOT(FonctionValidCon(QString)));
    maThreadConnect->start();
}
void Serveur::NewChat(QString TrameCreation)
{
   QString Validation = "Accp";
   int i = 0;
   while(i<6)
   {
       if(tChatroom[i] == TrameCreation)
       {
           Validation = "Refu";
       }
       i++;
   }
   i=0;
   if(Validation =="Accp")
   {
       while(i<6)
       {
           if(tChatroom[i]->isEmpty() || tChatroom[i]->isNull() )
           {
               tChatroom[i] = TrameCreation;
               i=6;
           }
       }
   }
   emit(siValidCre(Validation));
}
void Serveur::NewCon(QString TrameConnection)
{

}
