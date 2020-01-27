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

    double progress() const;

    QString fileName() const;

public slots:
    virtual void start() = 0;

signals:
    void finished(bool);

    void progressChanged();

    void nameChanged();

protected:
    double _progress;

    QString _fileName;

    bool checkForError(QFile& file, QTcpSocket& socket);

    void onError(QFile& file, QTcpSocket& socket);
};

#endif // TRANSMISSION_H
