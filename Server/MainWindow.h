#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include "TcpServer.h"

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QString m_msgStr;

    TcpServer* m_tcpServer;

    QLineEdit* m_portEdit;
    QLabel* m_connectCntLabel;
    QPlainTextEdit* m_displayTextEdit;
    QPushButton* m_listenBtn;

    void constructUI();
    void connectSlots();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onListenBtn();
    void onUpdateMsg(const QString& msg);
    void onUpdateConnectCnt(int cnt);
};

#endif // MAINWINDOW_H
