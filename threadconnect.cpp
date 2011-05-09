#include "threadconnect.h"
#include <QTcpSocket>

ThreadConnect::ThreadConnect(QTcpSocket *m_Socket) :
    QThread()
{
     sockClient = m_Socket;
}
//void ThreadConnect::FonctionConnect()
//{



//}
void ThreadConnect::run()
{
    sockClient->waitForReadyRead();
    baReception.append(sockClient->read(sockClient->bytesAvailable()));
    if(QString(baReception.left(4))=="Cre#")
    {
         emit (siNouvelleChat(QString(baReception.right(5))));
    }
    else
    {
        emit (siNouvelleCon(QString(baReception.right(5)),sockClient));
    }

}
void ThreadConnect::FonctionValidCre(QString Validation)
{
    if(Validation == "Accp")
    {
        sockClient->write(Validation.toAscii());
        sockClient->waitForBytesWritten();
        sockClient->waitForReadyRead();
        baReception.append(sockClient->read(sockClient->bytesAvailable()));
        if(QString(baReception.left(4))=="Con#")
        {
            emit (siNouvelleCon(QString(baReception.right(5)),sockClient));
        }
    }

}
void ThreadConnect::FonctionValidCon(QString Validation)
{
    if(Validation == "Accp")
    {
        sockClient->write(Validation.toAscii());
        sockClient->waitForBytesWritten();
    }
}
