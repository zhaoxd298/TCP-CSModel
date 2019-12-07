#include "MainWindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_tcpServer = new TcpServer;
    m_msgStr = "";

    constructUI();
    connectSlots();
}

void MainWindow::constructUI()
{
    QGridLayout* mainLayout = new QGridLayout(this);

    QLabel* portLabel = new QLabel(tr("端口："));
    portLabel->setMaximumWidth(30);
    m_portEdit = new QLineEdit;
    m_portEdit->setText("9999");
    m_listenBtn = new QPushButton(tr("监听"));
    mainLayout->addWidget(portLabel, 0, 0, 1, 1);
    mainLayout->addWidget(m_portEdit, 0, 1, 1, 4);
    mainLayout->addWidget(m_listenBtn, 0, 5, 1, 1);

    QLabel* connectCntLabel = new QLabel(tr("连接数量："));
    m_connectCntLabel = new QLabel(tr("0"));
    mainLayout->addWidget(connectCntLabel, 1, 0, 1, 1);
    mainLayout->addWidget(m_connectCntLabel, 1, 1, 1, 4);

    m_displayTextEdit = new QPlainTextEdit;
    m_displayTextEdit->setReadOnly(true);
    mainLayout->addWidget(m_displayTextEdit, 2, 0, 1, 6);

    resize(600, 400);
}

void MainWindow::connectSlots()
{
    connect(m_tcpServer, SIGNAL(sigUpdatemsg(QString)), this, SLOT(onUpdateMsg(QString)));
    connect(m_tcpServer, SIGNAL(sigUpdateConnectCnt(int)), this, SLOT(onUpdateConnectCnt(int)));
    connect(m_listenBtn, SIGNAL(clicked(bool)), this, SLOT(onListenBtn()));
}

MainWindow::~MainWindow()
{
    delete m_tcpServer;
}

void MainWindow::onListenBtn()
{
    bool ok = false;
    int port = m_portEdit->text().toInt(&ok);
    if (ok)
    {
        m_tcpServer->listenClient(port);
        m_listenBtn->setEnabled(false);
    }
}

void MainWindow::onUpdateMsg(const QString& msg)
{
    m_msgStr += "\n";
    m_msgStr += msg;

    m_displayTextEdit->setPlainText(m_msgStr);
}


void MainWindow::onUpdateConnectCnt(int cnt)
{
    m_connectCntLabel->setText(QString::number(cnt));
}
