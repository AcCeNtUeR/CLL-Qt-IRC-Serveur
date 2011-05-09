#include "serveur.h"
#include "ui_serveur.h"

Serveur::Serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Serveur)
{
    ui->setupUi(this);
    m_QTcpServer = new QTcpServer();
    ui->btnCommencer->hide();
}

Serveur::~Serveur()
{
    delete ui;
}

void Serveur::on_btnStart_clicked()
{
    ui->btnStart->hide();
    ui->btnCommencer->show();
    m_QTcpServer->listen(QHostAddress::Any,60123);
    connect(m_QTcpServer,SIGNAL(newConnection()),this,SLOT(Connection()));
}

void Serveur::on_btnCommencer_clicked()
{
    ui->btnStart->show();
    ui->btnCommencer->hide();
}

void Serveur::Connection()
{
    sockClient = m_QTcpServer->nextPendingConnection();
    QString ChatRoom = "allo";
    int i = 0;
    while(i < 6)
    {
        if(!tChatroom[i].isEmpty())
        {
            ChatRoom += tChatroom[i] +"\n";
        }
        i++;
    }
    sockClient->write(ChatRoom.toAscii());
    sockClient->waitForBytesWritten();

    //Connect au signaux de connection entre thread et threadprincipal
    ThreadConnect *maThreadConnect = new ThreadConnect(sockClient);
    connect(maThreadConnect,SIGNAL(siNouvelleCre(QString)),this,SLOT(NewChat(QString)));
    connect(maThreadConnect,SIGNAL(siNouvelleCon(QString,QTcpSocket)),this,SLOT(NewCon(QString,QTcpSocket*)));
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
            if(tChatroom[i].isEmpty() || tChatroom[i].isNull() )
            {
                tChatroom[i] = TrameCreation;
                i=6;
            }
        }
    }
    emit(siValidCre(Validation));
}
void Serveur::NewCon(QString TrameConnection,QTcpSocket *socket)
{
    QString chatroom="";
    QString User="";
    QString Validation="";
    int i =0;
    ////Séparation de la TrameConnection en Chatroom/User////
    while(TrameConnection[i]!='#')
    {
        chatroom += TrameConnection[i];
        i++;
    }
    i++;
    while(i<TrameConnection.count())
    {
        User+=TrameConnection[i];
        i++;
    }

    ////Trouve la position de la chatroom dans le tableau de ChatRoom ET socket////
    i=0;
    int posChat=0;
    //
    while(i<6)
    {
        if(tChatroom[i] == chatroom)
        {
            posChat = i;
            i=6;
        }
        i++;
    }
    ////Verifie si le socket de la chatroom a la position i est valide ou ouvert. Si non il "copy" le socket de connection à la position////
    i=0;
    while(i<6)
    {
        if(!tSockChatroom[posChat][i]->isValid())
        {
            tSockChatroom[posChat][i] = socket;
            Validation ="Accp";
            i=6;
        }
        i++;
    }
    ////Envoie de la validation////
    emit(siValidCon(Validation));
}
