#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QtNetwork>

using namespace std;

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    void tcpConnect(const QHostAddress ipAddress, const quint16 port);

public slots:

signals:
    void dataOutput(QByteArray* output);
    void logOutput(QString log);

private:
    QTcpSocket* socket = nullptr;
    QFile* outFile;

private slots:
    void readTcpData();
    void onDisconnected();
    void onConnected();
};

#endif // CLIENT_H