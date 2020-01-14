#ifndef RECIEVERSERVER_H
#define RECIEVERSERVER_H

#include <QTcpServer>

#include "recieverthread.h"

class RecieverServer : public QTcpServer
{
    Q_OBJECT

public:
    RecieverServer(QObject* parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // RECIEVERSERVER_H
