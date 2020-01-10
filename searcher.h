#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QUdpSocket>
#include <QDebug>
#include <QString>

class Searcher : public QObject
{
    Q_OBJECT

public:
    explicit Searcher(QObject *parent = nullptr);

    ~Searcher();

public slots:
    void send();

private slots:
    void onRecieved();

signals:
    void answerRecieved(QString, QHostAddress);

private:
    QUdpSocket* _sender;

    QUdpSocket* _listener;
};

#endif // SEARCHER_H
