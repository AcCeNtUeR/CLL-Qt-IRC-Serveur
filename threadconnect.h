#ifndef THREADCONNECT_H
#define THREADCONNECT_H
#include <QTcpSocket>
#include <QThread>
#include <serveur.h>

class ThreadConnect : public QThread
{
    Q_OBJECT
public:
    explicit ThreadConnect(QTcpSocket *m_Socket);
     QTcpSocket *sockClient;

private:   
    QByteArray baReception;
signals:
    void siNouvelleCon(QString);
    void siNouvelleChat(QString);
public slots:
    void FonctionValidCre(QString);
    void FonctionValidCon(QString);

protected:
    void run();

};

#endif // THREADCONNECT_H
