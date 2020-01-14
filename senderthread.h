#ifndef SENDERTHREAD_H
#define SENDERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QDebug>

#include "globals.h"

class SenderThread : public QThread
{
    Q_OBJECT

public:
    SenderThread(QHostAddress host, const QString filePath, QObject* parent);

    void run() override;

signals:
    void fileError(QFile::FileError error, QString errorString);

    void socketError(QTcpSocket::SocketError error, QString errorString);

private:
    QString _path;
    QHostAddress _host;
};

#endif // SENDERTHREAD_H
