#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QDataStream>
#include <QHostAddress>

#include "transmission.h"
#include "globals.h"

Q_DECLARE_METATYPE(QHostAddress)

class Reciever : public Transmission
{
    Q_OBJECT
    qintptr _socketDescriptor;

public:
    explicit Reciever(qintptr socketDescriptor, QObject *parent = nullptr);

signals:
    void peerConnected(QHostAddress);

public slots:
    void start() override;
};

#endif // RECIEVER_H
