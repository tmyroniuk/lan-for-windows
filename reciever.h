#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QDataStream>

#include "transmission.h"
#include "globals.h"

class Reciever : public Transmission
{
    Q_OBJECT
    qintptr _socketDescriptor;

public:
    explicit Reciever(qintptr socketDescriptor, QObject *parent = nullptr);

public slots:
    void start() override;
};

#endif // RECIEVER_H
