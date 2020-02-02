#ifndef RECIEVERSERVER_H
#define RECIEVERSERVER_H

#include <QTcpServer>
#include <QThread>

#include "reciever.h"

class RecieverServer : public QTcpServer
{
    Q_OBJECT

public:
    RecieverServer(QObject* parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    void onPeerConnected(const QHostAddress& host);

signals:
    void newConnection(Transmission*, QHostAddress);
};

#endif // RECIEVERSERVER_H
