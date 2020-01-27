#include "searcher.h"
#include "globals.h"

#include <QNetworkDatagram>
#include <QHostInfo>

Searcher::Searcher(QObject *parent) :
    QObject(parent),
    _sender(new QUdpSocket(this)),
    _listener(new QUdpSocket(this))
{
    _listener->bind(QHostAddress::Any, UDP_PORT);
    connect(_listener, &QUdpSocket::readyRead, this, &Searcher::onRecieved);
}

Searcher::~Searcher()
{
    _listener->close();
    delete _listener;
    delete _sender;
}

void Searcher::send()
{
    char data[1];
    data[0] = 0;
    _sender->writeDatagram(data, 1, QHostAddress::Broadcast, UDP_PORT);
}

void Searcher::onRecieved()
{
    while(_listener->hasPendingDatagrams()){
        auto datagram = _listener->receiveDatagram(1);
        if(datagram.data().at(0) == 0){
            _sender->writeDatagram("~", 1, datagram.senderAddress(), UDP_PORT);
        } else if (datagram.data().at(0) == '~'){
            auto address = QHostAddress(datagram.senderAddress().toIPv4Address());
            emit answerRecieved(
                QHostInfo::fromName(address.toString()).hostName(),
                address);
        }
    }
}
