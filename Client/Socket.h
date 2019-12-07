#ifndef SOCKET_H
#define SOCKET_H


#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

class Socket : public QObject
{
    Q_OBJECT

private:
    static Socket* c_instance;

    int m_port;
    QString m_ip;
    QHostAddress* m_serverIP;
    QTcpSocket* m_tcpSocket;

    bool m_connectStatus;      // 标识是否连接上服务器

private:
    Socket();
    Socket(const Socket&);
    Socket& operator= (const Socket&);
    bool construct();       // 二阶构造

public:
    static Socket* GetInstance();
    ~Socket();

    bool connectToServer(const QString& ip, int port);
    bool connectStatus();

    bool sendMsg(const char* buf, int size);
    bool sendMsg(QString msg);

signals:
    void sigConnected();
    void sigDisconnected();
    void sigDataReceived(const QString& msg);

protected slots:
    void onConnected();
    void onDisconnected();
    void onDataReceived();
};

#endif // SOCKET_H
