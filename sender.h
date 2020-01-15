#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QDataStream>
#include <QFileInfo>
#include <QThread>
#include <QUrl>

#include "globals.h"

class Sender : public QObject
{
    Q_OBJECT

    QUrl _filePath;
    QHostAddress _host;

public:
    explicit Sender(QHostAddress host, const QUrl filePath, QObject *parent = nullptr);

signals:
    void fileError(QFile::FileError error, QString errorString);

    void socketError(QTcpSocket::SocketError error, QString errorString);

public slots:
    void startTransmission();
};

#endif // SENDER_H
