#ifndef RECIEVERTHREAD_H
#define RECIEVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QString>
#include <QDataStream>
#include <QFile>
#include <QDebug>

#include "globals.h"

class RecieverThread : public QThread
{
    Q_OBJECT
public:
    RecieverThread(qintptr socketDescriptor, QObject* parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError error, QString errorString);

    void fileError(QFile::FileError error, QString errorString);

private:
    qintptr _socketDescriptor;
};

#endif // RECIEVERTHREAD_H
