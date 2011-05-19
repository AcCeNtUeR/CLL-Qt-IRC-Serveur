#ifndef THREADSERVEUR_H
#define THREADSERVEUR_H
#include <QTcpSocket>
#include <QThread>
#include <serveur.h>

class ThreadServeur : public QThread
{
    Q_OBJECT
public:
    explicit ThreadServeur(QTcpSocket *m_Socket);
    QTcpSocket *sockClient;
    bool m_etat;

signals:
    void Fin(QTcpSocket*);

    void Envoie(QTcpSocket*,QString);

public slots:
   // void Lecture();

    void run();

};

#endif // THREADSERVEUR_H
