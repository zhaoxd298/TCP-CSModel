#include "Widget.h"
#include <QGridLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_displayStr = "";

    m_socket = Socket::GetInstance();

    constructUI();
    connectSlots();

}

Widget::~Widget()
{

}

void Widget::constructUI()
{
    QGridLayout* mainLayout = new QGridLayout(this);

    QLabel* portLabel = new QLabel(tr("端口："));
    portLabel->setMaximumWidth(30);
    m_portEdit = new QLineEdit;
    m_portEdit->setText("9999");
    mainLayout->addWidget(portLabel, 0, 0, 1, 1);
    mainLayout->addWidget(m_portEdit, 0, 1, 1, 4);

    QLabel* ipLabel = new QLabel(tr("IP地址："));
    m_ipEdit = new QLineEdit;
    m_ipEdit->setText("127.0.0.1");
    m_connectBtn = new QPushButton(tr("连接"));
    mainLayout->addWidget(ipLabel, 1, 0, 1, 1);
    mainLayout->addWidget(m_ipEdit, 1, 1, 1, 4);
    mainLayout->addWidget(m_connectBtn, 1, 5, 1, 1);

    m_displayTextEdit = new QPlainTextEdit;
    m_displayTextEdit->setReadOnly(true);
    mainLayout->addWidget(m_displayTextEdit, 2, 0, 1, 6);

    m_inputTextEdit = new QPlainTextEdit;
    m_inputTextEdit->setMaximumHeight(100);
    mainLayout->addWidget(m_inputTextEdit, 3, 0, 1, 6);

    m_sendBtn = new QPushButton(tr("发送"));
    mainLayout->addWidget(m_sendBtn, 4, 5, 1, 1);

    resize(600, 400);
}

void Widget::connectSlots()
{
    connect(m_sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendBtn()));
    connect(m_connectBtn, SIGNAL(clicked(bool)), this, SLOT(onConnectBtn()));
    connect(m_socket, SIGNAL(sigDataReceived(QString)), this, SLOT(onDataReceived(QString)));
}

void Widget::onSendBtn()
{
    QString str = m_inputTextEdit->toPlainText();
    if (m_socket)
    {
        m_socket->sendMsg(str);
    }

    m_displayStr += "\n";
    m_displayStr += QString(tr("我："));
    m_displayStr += str;
    m_displayTextEdit->setPlainText(m_displayStr);

    m_inputTextEdit->clear();
}


void Widget::onConnectBtn()
{
    bool ok;
    QString ip = m_ipEdit->text();
    int port = m_portEdit->text().toInt(&ok);

    if (m_socket && !ip.isEmpty() && ok)
    {
        m_socket->connectToServer(ip, port);
    }

    m_connectBtn->setEnabled(false);
}


void Widget::onDataReceived(const QString& msg)
{
    m_displayStr += "\n";
    m_displayStr += QString(tr("Server："));
    m_displayStr += msg;
    m_displayTextEdit->setPlainText(m_displayStr);
}
