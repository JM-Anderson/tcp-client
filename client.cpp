#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    outFile = new QFile("out.txt");
    socket = new QTcpSocket();
    connect( socket, &QAbstractSocket::disconnected, this, &Client::onDisconnected );
    connect( socket, &QAbstractSocket::connected, this, &Client::onConnected );
    connect( socket, &QIODevice::readyRead, this, &Client::readTcpData );
}

void Client::readTcpData()
{
    emit logOutput("Receiving data:");

    QByteArray data;
    while (!socket->atEnd()){
        data = socket->read(8);
        emit dataOutput(&data);
    }

    emit logOutput("End of data");

}

void Client::tcpConnect(const QHostAddress ipAddress, const quint16 port) {
    socket->abort();
    socket->connectToHost(ipAddress, port);
}

void Client::onDisconnected()
{
    emit logOutput("Closing socket");
}

void Client::onConnected()
{
    emit logOutput(QString("Connected to: %1:%2")
                   .arg(socket->peerAddress().toString())
                   .arg(socket->peerPort()));
}
