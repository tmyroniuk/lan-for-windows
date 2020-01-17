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
    QHostAddress _host;
    QUrl _filePath;

public:
    explicit Sender(QHostAddress host, const QUrl filePath, QObject *parent = nullptr);

signals:
    void finished(bool);

public slots:
    void start();
    
private slots:
    void onError(QFile& file, QTcpSocket& socket);
};

#endif // SENDER_H
