#ifndef SERVEUR_H
#define SERVEUR_H

#include <QMainWindow>
#include <QtGui>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "threadconnect.h"

namespace Ui {
    class Serveur;
}

class Serveur : public QMainWindow
{
    Q_OBJECT

public:
    explicit Serveur(QWidget *parent = 0);
    ~Serveur();

signals:
   void siNouvelleConnection();
   void siValidCon(QString);
   void siValidCre(QString);


private slots:
    void on_btnStart_clicked();

    void on_btnCommencer_clicked();

    void Connection();

    void NewCon(QString,QTcpSocket*);

    void NewChat(QString);


private:
    Ui::Serveur *ui;
    QTcpServer *m_QTcpServer;
    QString tChatroom[6];
    QTcpSocket *tSockChatroom[6][6];
    QTcpSocket *sockClient;

};

#endif // SERVEUR_H
