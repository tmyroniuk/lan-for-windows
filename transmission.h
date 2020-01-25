#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QObject>
#include <QFile>
#include <QTcpSocket>

class Transmission : public QObject
{
    Q_OBJECT
public:
    explicit Transmission(QObject *parent = nullptr);

public slots:
    virtual void start() = 0;

signals:
    void finished(bool);

protected:
    bool checkForError(QFile& file, QTcpSocket& socket);

    void onError(QFile& file, QTcpSocket& socket);
};

#endif // TRANSMISSION_H
