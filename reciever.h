#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QThread>

#include "globals.h"

class Reciever : public QObject
{
    Q_OBJECT
    qintptr _socketDescriptor;

public:
    explicit Reciever(qintptr socketDescriptor, QObject *parent = nullptr);

signals:    
    void finished(bool);

public slots:
    void start();
    
private slots:
    void onError(QFile& file, QTcpSocket& socket);
};

#endif // RECIEVER_H
