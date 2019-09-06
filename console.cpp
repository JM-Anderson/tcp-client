#include "console.h"

Console::Console(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
}

Console::~Console()
{
    delete ui;
}

void Console::on_connectButton_clicked()
{
    quint16 port = 1234;
    Client* client = new Client();
    client->tcpConnect(QHostAddress::LocalHost, port);

    connect(client, &Client::dataOutput,
            [=]( const QByteArray* output ) { consolePrintLn(*output); } );

    connect(client, &Client::logOutput, this, &Console::consolePrintLn);
}

void Console::on_clearConsoleButton_clicked()
{
    ui->consoleTextBox->setPlainText("");
}

void Console::consolePrintLn(const QString output) {
    ui->consoleTextBox->appendPlainText(output);
}


