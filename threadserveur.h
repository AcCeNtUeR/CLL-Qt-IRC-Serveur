#ifndef THREADSERVEUR_H
#define THREADSERVEUR_H

#include <QThread>

class ThreadServeur : public QThread
{
    Q_OBJECT
public:
    explicit ThreadServeur(QObject *parent = 0);

signals:

public slots:

};

#endif // THREADSERVEUR_H
