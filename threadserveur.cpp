#include "threadserveur.h"
#include "serveur.h"

ThreadServeur::ThreadServeur(QTcpSocket *m_Socket):
    QThread()
{
   sockClient = m_Socket;
   m_etat = true;
}

void ThreadServeur::run()
{
    QByteArray baReception;
    while(m_etat)
    {
        baReception.clear();
             sockClient->waitForReadyRead(-1); // Attente des données pendant 0.1 sec maximum
             baReception.append(sockClient->read(sockClient->bytesAvailable())); // Lecture des donnée

             if(QString(baReception.left(4)) == QString("Env#"))
             {
                 emit(Envoie(sockClient,QString(baReception.right(baReception.length()))));
             }
             if(QString(baReception.left(4)) == QString("Fin#"))
             {
                 m_etat = false;
                emit(Fin(sockClient));
             }
    }
}
