#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>

#include "globals.h"

class Reciever : public QObject
{
    Q_OBJECT

    qintptr _socketDescriptor;

public:
    explicit Reciever(qintptr _socketDescriptor, QObject *parent = nullptr);

signals:
    void error(QTcpSocket::SocketError error, QString errorString);

    void fileError(QFile::FileError error, QString errorString);

public slots:
    void recieveTransmission();

};

#endif // RECIEVER_H
