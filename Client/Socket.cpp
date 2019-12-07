#include "Socket.h"
#include <QByteArray>


Socket* Socket::c_instance = NULL;

Socket::Socket()
{
    m_connectStatus = false;
    m_port = 0;
    m_ip = "";
}

Socket::~Socket()
{
    delete m_serverIP;
    delete m_tcpSocket;
}

bool Socket::construct()
{
    m_serverIP = new QHostAddress();
    m_tcpSocket = new QTcpSocket();

    if (!(m_serverIP && m_tcpSocket)) {
        return false;
    }

    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onDataReceived()));

    return true;
}

Socket* Socket::GetInstance()
{
    if (c_instance == NULL) {
        c_instance = new Socket();
        // 若第二阶段构造失败，返回 NULL
        if (!(c_instance && c_instance->construct())) {
            delete c_instance;
            c_instance = NULL;
        }
    }

    return c_instance;
}

bool Socket::connectToServer(const QString& ip, int port)
{
    m_ip = ip;
    m_port = port;

    if (m_connectStatus)
    {
        return true;
    }

    if (!m_serverIP->setAddress(ip)) {
        return false;
    }

    m_tcpSocket->connectToHost(*m_serverIP, port);

    return true;
}

bool Socket::connectStatus()
{
    return m_connectStatus;
}

bool Socket::sendMsg(const char* buf, int size)
{
    if (NULL==buf || size<=0) {
        return false;
    }

    int ret = m_tcpSocket->write(buf, size);
    if (ret != size) {
        return false;
    }

    return true;
}

bool Socket::sendMsg(QString msg)
{
    return sendMsg(msg.toLocal8Bit(), msg.toLocal8Bit().size());
}

void Socket::onConnected()
{
    m_connectStatus = true;

    emit sigConnected();
}

void Socket::onDisconnected()
{
    m_connectStatus = false;

    emit sigDisconnected();
}

void Socket::onDataReceived()
{
    while (m_tcpSocket->bytesAvailable() > 0)
    {
        int len = m_tcpSocket->bytesAvailable();

        QByteArray array = m_tcpSocket->read(len);
        QString msg = QString::fromLocal8Bit(array);

        emit sigDataReceived(msg);
    }
}
