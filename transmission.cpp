#include "transmission.h"

Transmission::Transmission(QObject *parent) : QObject(parent), _progress() {}

bool Transmission::checkForError(QFile &file, QTcpSocket &socket)
{
    if(file.error() != QFile::NoError || socket.error() != QTcpSocket::UnknownSocketError){
        onError(file, socket);
        return true;
    }
    return false;
}

void Transmission::onError(QFile& file, QTcpSocket& socket)
{
    qDebug() <<"file" << file.error() << file.errorString();
    qDebug() <<"socket" << socket.error() << socket.errorString();
    if(file.isOpen()) file.close();
    if(socket.state() == QTcpSocket::ConnectedState) socket.disconnectFromHost();
    emit finished(false);
}

double Transmission::progress() const { return _progress; }

QString Transmission::fileName() const { return _fileName; }
