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
    sockClient->waitForReadyRead(-1);
    baReception.append(sockClient->read(sockClient->bytesAvailable()));
    if(QString(baReception.left(4))=="Cre#")
    {
         emit (siNouvelleCre(QString(baReception.right(5))));
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
        sockClient->waitForReadyRead(-1);
        baReception.clear();
        baReception.append(sockClient->read(sockClient->bytesAvailable()));
        if(QString(baReception.left(4))=="Con#")
        {

            QString ba(baReception);
            QString bal(baReception.right(5));
            int all = 0;
            emit (siNouvelleCon(QString(baReception.right(5)),sockClient));
        }
    }
    else
    {
        ThreadConnect::run();
    }

}
void ThreadConnect::FonctionValidCon(QString Validation)
{
    if(Validation == "Accp")
    {
        sockClient->write(Validation.toAscii());
        sockClient->waitForBytesWritten();
    }
    else
    {
        ThreadConnect::run();
    }
}
