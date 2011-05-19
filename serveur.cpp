#include "serveur.h"
#include "ui_serveur.h"

Serveur::Serveur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Serveur)
{
    ui->setupUi(this);
    ui->btnCommencer->hide();
    tChatroom[0] = "XD";
    tChatroom[2] = "Allo";
    compteur=0;

}

Serveur::~Serveur()
{
    m_QTcpServer->close();


    delete ui;
}

void Serveur::on_btnStart_clicked()
{

    int i =0;
    int j =0;
    while(i<6)
    {
        while(j<6)
        {
            tboolChatroom[i][j] = false;
            j++;
        }
        j=0;
        i++;
    }
    m_QTcpServer = new QTcpServer();
    ui->btnStart->hide();
    ui->btnCommencer->show();
    m_QTcpServer->listen(QHostAddress::Any,60123);
    connect(m_QTcpServer,SIGNAL(newConnection()),this,SLOT(Connection()));
}

void Serveur::on_btnCommencer_clicked()
{
    ui->btnStart->show();
    ui->btnCommencer->hide();
    m_QTcpServer->close();

}

void Serveur::Connection()
{
   // ThreadConnect *maThreadConnect = new ThreadConnect(m_QTcpServer->nextPendingConnection());
    QTcpSocket *sockClient = m_QTcpServer->nextPendingConnection();
    QString ChatRoom = "";
    int i = 0;
    compteur++;
    if(compteur==2)
    {
        i=0;
    }
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
    bool connection = connect(maThreadConnect,SIGNAL(siNouvelleCon(QString,QTcpSocket*)),this,SLOT(NewCon(QString,QTcpSocket*)));
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
            i++;
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
        if(tboolChatroom[posChat][i] ==false)
        {
            tSockChatroom[posChat][i] = socket;
            tboolChatroom[posChat][i]=true;
            Validation ="Accp";
            i=6;
        }
        i++;
    }
    ThreadServeur *mathreadLecture = new ThreadServeur(socket);
    connect(mathreadLecture,SIGNAL(Fin(QTcpSocket*)),this,SLOT(SortieChat(QTcpSocket*)));
    connect(mathreadLecture,SIGNAL(Envoie(QTcpSocket*,QString)),this,SLOT(Envoie(QTcpSocket*,QString)));
    ////Envoie de la validation////
    mathreadLecture->start();
    emit(siValidCon(Validation));
}
void Serveur::SortieChat(QTcpSocket *socket)
{
    int posChat =0;
    int i=0;
    while(posChat<6)
    {
        i=0;
        while(i<6)
        {
            if(tSockChatroom[posChat][i] == socket)
            {
                tSockChatroom[posChat][i]->close();
                tboolChatroom[posChat][i] =false;
                i=6;
                posChat=6;
            }
            i++;
        }
        posChat++;
    }

}
void Serveur::Envoie(QTcpSocket *socket,QString Trame)
{
    int posChat =0;
    int i=0;
    int j=0;
    while(posChat<6)
    {
        i=0;
        while(i<6)
        {
            if(tSockChatroom[posChat][i] == socket)
            {
                while(j<6)
                {
                 if( tboolChatroom[posChat][j]==true)
                 {
                 tSockChatroom[posChat][j]->write(Trame.toAscii());
                 tSockChatroom[posChat][j]->waitForBytesWritten();
                 }
                 j++;
                }
                i=6;
                posChat=6;
            }
            i++;
        }
        posChat++;
    }
 }
