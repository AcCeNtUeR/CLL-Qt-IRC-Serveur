#include "threadconnect.h"
#include <QTcpSocket>

ThreadConnect::ThreadConnect(QTcpSocket *m_Socket) :
    QThread()
{
     sockClient = m_Socket;
   //  connect (sockClient, SIGNAL(disconnected()), this, SLOT(slDeconnexion()));
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
         emit (siNouvelleCre(QString(baReception.right(baReception.length() - 4))));
    }
    else
    {
        emit (siNouvelleCon(QString(baReception.right(baReception.length() - 4)),sockClient));
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
            emit(siNouvelleCon(QString(baReception.right(baReception.length() - 4)),sockClient));
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

/*void ThreadConnect::slDeconnexion()
{

}*/
