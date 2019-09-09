#ifndef CONSOLE_H
#define CONSOLE_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include "ui_console.h"
#include "client.h"

using namespace std;

namespace Ui {
class Console;
}

class Console : public QMainWindow
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = nullptr);
    ~Console();

public slots:
    void consolePrintLn(const QString output);

private slots:
    void on_connectButton_clicked();

    void on_clearConsoleButton_clicked();

    void on_sendButton_clicked();

    void on_msgEdit_returnPressed();

private:
    Ui::Console *ui;
    Client* client;
};

#endif // CONSOLE_H
