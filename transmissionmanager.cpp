#include "transmissionmanager.h"
#include "globals.h"

#include <QTimer>
#include <QHostInfo>


TransmissionManager::TransmissionManager(QObject *parent) :
    QObject(parent),
    _listener(new RecieverServer(this)),
    _list(new QVector<Peer*>())
{
    connect(_listener, &RecieverServer::newConnection, this, &TransmissionManager::onNewConnection);
    _listener->listen(QHostAddress::Any, TCP_PORT);
}

TransmissionManager::~TransmissionManager() {
    delete _listener;
    for(auto& i: *_list) delete i;
    delete _list;
}

QVector<Peer*>* TransmissionManager::peerList() { return _list; }

void TransmissionManager::send(int i, const QUrl& filePath) {
    auto thread = new QThread;
    auto sender = new Sender(_list->value(i)->address(), filePath);
    sender->moveToThread(thread);
    _list->value(i)->addTransmission(sender);
    connect(sender, &Transmission::finished, this, &TransmissionManager::onFinished);
    connect(sender, &Sender::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, sender, &QObject::deleteLater);
    connect(thread, &QThread::started, sender, &Sender::start);
    thread->start();
}

void TransmissionManager::refresh()
{
    emit startRefresh();
    auto oldList = _list;
    _list = new QVector<Peer*>();
    emit finishRefresh();

    emit startRefresh();
    connect(&_searcher, &Searcher::answerRecieved, this,
        [this, oldList](const QString& name, const QHostAddress& address) {
            for(auto i: *oldList)
                if(i -> address() == address && !(i -> transmissions() -> empty())) {
                    _list->append(i);
                    oldList->removeOne(i);
                    return;
                }
            _list->append(new Peer(name, address));

    });

    _searcher.send();

    QTimer::singleShot(REFRESH_TIME, [this, oldList]() {
        _searcher.disconnect(this);
        for(auto& i: *oldList) delete i;
        qDebug() <<(oldList == nullptr);
        delete oldList;
        qDebug() <<(oldList == nullptr);
        emit finishRefresh();
    });
}

void TransmissionManager::onNewConnection(Transmission *transmission, const QHostAddress& address)
{
    connect(transmission, &Transmission::finished, this, &TransmissionManager::onFinished);
    for(auto i: *_list) if(i -> address() == address) {
        i -> addTransmission(transmission);
        return;
    }
    auto temp = new Peer(QHostInfo::fromName(address.toString()).hostName(), address);
    temp -> addTransmission(transmission);
    _list->append(temp);
    emit dataChanged(_list->size() - 1);
}

void TransmissionManager::onFinished(const bool& status, const QString& fileName, const QString& errorString)
{
    if(status) emit complete(fileName);
    else emit error(fileName, errorString);

}
