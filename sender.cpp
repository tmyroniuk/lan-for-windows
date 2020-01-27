#include "sender.h"

Sender::Sender(QHostAddress host, const QUrl filePath, QObject *parent) :
    Transmission(parent),
    _host(host),
    _filePath(filePath) {}

void Sender::start()
{
    QTcpSocket socket;
    QFile file(_filePath.toLocalFile());
    _fileName = _filePath.fileName();
    emit nameChanged();

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
    qint64 fileSize = file.size();
    qint64 currentSize = 0;
    QDataStream wrightStream(&block, QIODevice::WriteOnly);
    wrightStream.setVersion(QDataStream::Qt_5_12);
    wrightStream << _fileName;
    wrightStream << fileSize;
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
        currentSize += block.size();
        _progress = 1.0 * currentSize / fileSize;
        emit progressChanged();
    }

    //Disconnect and close file
    file.close();
    socket.disconnectFromHost();
    socket.waitForDisconnected(TIMEOUT);

    qDebug() << "sending finised" << file.fileName();
    emit finished(true);
}

