#ifndef SERVEUR_H
#define SERVEUR_H

#include <QMainWindow>

namespace Ui {
    class Serveur;
}

class Serveur : public QMainWindow
{
    Q_OBJECT

public:
    explicit Serveur(QWidget *parent = 0);
    ~Serveur();

private:
    Ui::Serveur *ui;
};

#endif // SERVEUR_H
