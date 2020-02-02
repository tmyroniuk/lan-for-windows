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
    QString errorString;
    if(file.error() != QFile::NoError) errorString.append(file.errorString() + "\n");
    if(socket.error() != QTcpSocket::UnknownSocketError) errorString.append(socket.errorString() + "\n");

    if(file.isOpen()) file.close();
    if(socket.state() == QTcpSocket::ConnectedState) socket.disconnectFromHost();
    emit finished(false, _fileName, errorString);
}

double Transmission::progress() const { return _progress; }

QString Transmission::fileName() const { return _fileName; }
