#include "console.h"

Console::Console(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);

    client = new Client();
    connect(client, &Client::dataOutput,
            [=]( const QByteArray* output ) { consolePrintLn(*output); } );

    connect(client, &Client::logOutput, this, &Console::consolePrintLn);
}

Console::~Console()
{
    delete ui;
}

void Console::on_connectButton_clicked()
{
    quint16 port = 1234;
    client->tcpConnect(QHostAddress::LocalHost, port);
}

void Console::on_clearConsoleButton_clicked()
{
    ui->consoleTextBox->setPlainText("");
}

void Console::consolePrintLn(const QString output) {
    ui->consoleTextBox->appendPlainText(output);
}

void Console::on_sendButton_clicked()
{
    client->sendMsg(ui->msgEdit->text().toUtf8());
}

void Console::on_msgEdit_returnPressed()
{
    on_sendButton_clicked();
}
