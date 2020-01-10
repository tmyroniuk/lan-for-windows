#ifndef RECIEVERTHREAD_H
#define RECIEVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QString>
#include <QDataStream>

class RecieverThread : public QThread
{
    Q_OBJECT
public:
    RecieverThread(qintptr socketDescriptor, QObject* parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError error, QString errorString);

    void recieved(QString);

private:
    qintptr _socketDescriptor;
};

#endif // RECIEVERTHREAD_H
