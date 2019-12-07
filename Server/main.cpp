#include "MainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //TcpServer* tcpServer = new TcpServer(0, 9999);

    MainWindow w;
    w.show();

    return a.exec();
}
