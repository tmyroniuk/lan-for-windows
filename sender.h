#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QHostAddress>
#include <QDataStream>
#include <QFileInfo>
#include <QUrl>

#include "transmission.h"
#include "globals.h"

class Sender : public Transmission
{
    Q_OBJECT
    QHostAddress _host;
    QUrl _filePath;

public:
    explicit Sender(QHostAddress host, const QUrl filePath, QObject *parent = nullptr);

public slots:
    void start() override;
};

#endif // SENDER_H
