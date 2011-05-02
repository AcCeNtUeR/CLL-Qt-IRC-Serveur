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
    ThreadEnvoie *maThreadEnvoie = new ThreadEnvoie(m_QTcpServer->nextPendingConnection());
    connect(this,SIGNAL(siImage(QByteArray)),maThreadEnvoie,SLOT(Image(QByteArray)));
    maThreadEnvoie->start();
}
