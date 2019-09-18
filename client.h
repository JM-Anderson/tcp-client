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
    void sendMsg(QByteArray msg);

public slots:

signals:
    void dataOutput(QByteArray* output);
    void logOutput(QString log);

private:
    QTcpSocket* socket = nullptr;
    QFile* outFile;

    const int frameSize = 480*640;
    const int pixelBytes = sizeof(quint16);

    QByteArray inBuffer;

private slots:
    void readTcpData();
    void onDisconnected();
    void onConnected();
};

#endif // CLIENT_H
