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

signals:
    void fileError(QFileDevice::FileError error, QString errorString);

    void socketError(QAbstractSocket::SocketError error, QString errorString);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // RECIEVERSERVER_H
