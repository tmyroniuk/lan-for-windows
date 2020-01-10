#ifndef SENDERTHREAD_H
#define SENDERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>

class SenderThread : public QThread
{
    Q_OBJECT

public:
    SenderThread(QHostAddress host, quint16 port, const QString data, QObject* parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError error, QString errorString);

private:
    QString _data;
    QHostAddress _host;
    quint16 _port;
};

#endif // SENDERTHREAD_H
