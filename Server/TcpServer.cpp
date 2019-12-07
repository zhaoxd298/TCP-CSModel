#include "TcpServer.h"

#include <QDebug>

TcpServer::TcpServer(QObject *parent, int port)
    :QTcpServer(parent)
{
    if (0 != port)
    {
        listen(QHostAddress::Any, port);
    }
}

void TcpServer::listenClient(int port)
{
    listen(QHostAddress::Any, port);
}

void TcpServer::incomingConnection(int socketDescriptor)
{
    TcpSocket *tcpSocket = new TcpSocket(this);
    connect(tcpSocket, SIGNAL(receivedMsg(QString,int)), this, SLOT(slotReceivedMsg(QString,int)));
    connect(tcpSocket, SIGNAL(disconnected(int)), this, SLOT(slotDisconnected(int)));

    tcpSocket->setSocketDescriptor(socketDescriptor);

    tcpSocketList.append(tcpSocket);

    emit sigUpdateConnectCnt(tcpSocketList.size());

    QString str = "Connected by IP:" + tcpSocket->localAddress().toString();
    emit sigUpdatemsg(str);
    //qDebug() << "Connected by IP:" << tcpSocket->localAddress().toString();
}

void TcpServer::slotReceivedMsg(QString msg, int descriptor)
{
    for(int i=0;i<tcpSocketList.count();i++)
    {
        QTcpSocket *item = tcpSocketList.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            QString str = item->localAddress().toString() + ":" + msg;
            emit sigUpdatemsg(str);

            if ('\n' == msg[msg.size()-1])
            {
                msg.remove(msg.size()-1, 1);
            }
            QString replyStr = QString(tr("我已收到信息")) + "[" + msg + "]";
            item->write(replyStr.toLocal8Bit(), replyStr.toLocal8Bit().size());
            return;
        }
    }
}

void TcpServer::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpSocketList.count();i++)
    {
        QTcpSocket *item = tcpSocketList.at(i);
        if(item->socketDescriptor() == descriptor)
        {
            tcpSocketList.removeAt(i);

            emit sigUpdateConnectCnt(tcpSocketList.size());

            QString str = "Disconnected by IP:" + item->localAddress().toString();
            emit sigUpdatemsg(str);
            return;
        }
    }
    return;
}
