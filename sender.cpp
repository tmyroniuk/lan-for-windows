#include "sender.h"

Sender::Sender(QHostAddress host, const QUrl filePath, QObject *parent) :
    Transmission(parent),
    _host(host),
    _filePath(filePath) {}

void Sender::start()
{
    QTcpSocket socket;
    QFile file(_filePath.toLocalFile());

    //Open file
    if(!file.open(QIODevice::ReadOnly)){
        onError(file, socket);
        return;
    }

    //Connect
    socket.connectToHost(_host, TCP_PORT);
    if (!socket.waitForConnected(TIMEOUT)){
        onError(file, socket);
        return;
    }

    //Sending data
    QByteArray block;
    QDataStream wrightStream(&block, QIODevice::WriteOnly);
    wrightStream.setVersion(QDataStream::Qt_5_12);
    wrightStream << _filePath.fileName();
    wrightStream << file.size();
    socket.write(block);
    socket.flush();

    //Sending file
    while(!file.atEnd()){
        block = file.read(BLOCK_LEN);
        if(checkForError(file, socket)) return;
        while(socket.bytesToWrite() > MAX_BOOFER_SIZE){
            socket.waitForBytesWritten(TIMEOUT);
            if(checkForError(file, socket)) return;
        }
        socket.write(block);
    }

    //Disconnect and close file
    file.close();
    socket.disconnectFromHost();
    socket.waitForDisconnected(TIMEOUT);

    qDebug() << "sending finised" << file.fileName();
    emit finished(true);
}

