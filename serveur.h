#ifndef SERVEUR_H
#define SERVEUR_H

#include <QMainWindow>
#include <QtGui>
#include <QTcpServer>
#include <QThread>
#include "threadserveur.h"

namespace Ui {
    class Serveur;
}

class Serveur : public QMainWindow
{
    Q_OBJECT

public:
    explicit Serveur(QWidget *parent = 0);
    ~Serveur();

private slots:
    void on_btnStart_clicked();

    void on_btnCommencer_clicked();

    void Connection();

private:
    Ui::Serveur *ui;
    QTcpServer *m_QTcpServer;
};

#endif // SERVEUR_H
