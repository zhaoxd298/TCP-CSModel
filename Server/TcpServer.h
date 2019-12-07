#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "TcpSocket.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
private:
    QList<TcpSocket*> tcpSocketList;

public:
    TcpServer(QObject *parent=0, int port=0);
    void listenClient(int port);

signals:
    void sigUpdatemsg(const QString&);
    void sigUpdateConnectCnt(int cnt);

public slots:
    void slotReceivedMsg(QString,int);
    void slotDisconnected(int);

protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
