#include "transmissionmanager.h"
#include "globals.h"

#include <QTimer>

TransmissionManager::TransmissionManager(QObject *parent) :
    QObject(parent),
    _listener(new RecieverServer(this))
{
    _listener->listen(QHostAddress::Any, TCP_PORT);
}

TransmissionManager::~TransmissionManager() {delete _listener;}

QVector<Peer*>* TransmissionManager::peerList() { return &_list; }

void TransmissionManager::send(int i, const QUrl& filePath) {
    qDebug() << filePath;
    auto thread = new QThread;
    auto sender = new Sender(_list[i]->address(), filePath);
    sender->moveToThread(thread);
    _list[i]->addTransmission(sender);
    connect(sender, &Sender::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::started, sender, &Sender::start);
    thread->start();
}

void TransmissionManager::refresh()
{
    _list.clear();

    emit startRefresh();
    connect(&_searcher, &Searcher::answerRecieved, this,
        [this](const QString& name, const QHostAddress& address){ _list.append(new Peer(name, address)); });

    _searcher.send();

    QTimer::singleShot(REFRESH_TIME, [this]() {
        _searcher.disconnect(this);
        emit finishRefresh();
    });
}

void TransmissionManager::clear()
{
    emit startRefresh();
    _list.clear();
    emit finishRefresh();
}
