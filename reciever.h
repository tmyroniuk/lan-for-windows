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
    explicit Reciever(qintptr _socketDescriptor, QObject *parent = nullptr);

signals:    
    void fileError(QFileDevice::FileError error, QString errorString);

    void socketError(QAbstractSocket::SocketError error, QString errorString);

public slots:
    void recieveTransmission();
};

#endif // RECIEVER_H
