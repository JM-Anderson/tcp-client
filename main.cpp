#include <QApplication>
#include <QtNetwork>
#include "client.h"
#include "console.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Console console;
    console.show();

    return a.exec();
}


