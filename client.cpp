#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    outFile = new QFile("out.txt");
    socket = new QTcpSocket();
    connect( socket, &QAbstractSocket::disconnected, this, &Client::onDisconnected );
    connect( socket, &QAbstractSocket::connected, this, &Client::onConnected );
    connect( socket, &QIODevice::readyRead, this, &Client::readTcpData );
}

/*
 * If reimplementing this method, note that TCP data arrives in BigEndian
 * and hardware integers are most likely stored with LittleEndian. QDataStream
 * automatically reads in BigEndian and converts to the correct endianness.
*/
void Client::readTcpData()
{
    inBuffer.append(socket->readAll());

    while (inBuffer.size() >= frameSize*pixelBytes) {
        QDataStream pixStream(&inBuffer, QIODevice::ReadOnly);
        QVector<quint16> frame;
        for (int i=0; i < frameSize; i++) {
            quint16 pix;
            pixStream >> pix;
            frame.append(pix);
        }

        emit logOutput(QString("Finished one frame %1 %2").arg(frame.first()).arg(frame.last()));
        inBuffer.remove(0, frameSize*pixelBytes);
    }
}

void Client::sendMsg(QByteArray msg) {
    if (msg.size() < 1) {
        logOutput("Can't send empty message");
        return;
    }
    socket->write(msg);
    if (socket->waitForBytesWritten()) {
        emit logOutput("Message sent");
    } else {
        emit logOutput("Message not sent");
    }
}

void Client::tcpConnect(const QHostAddress ipAddress, const quint16 port) {
    socket->abort();
    inBuffer.clear();
    socket->connectToHost(ipAddress, port);
}

void Client::onDisconnected()
{
    emit logOutput("Closing socket");
    outFile->close();
}

void Client::onConnected()
{
    emit logOutput(QString("Connected to: %1:%2")
                   .arg(socket->peerAddress().toString())
                   .arg(socket->peerPort()));

    outFile->open(QIODevice::WriteOnly);
}
