#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QString>
#include "Socket.h"

class Widget : public QWidget
{
    Q_OBJECT
private:
    QString m_displayStr;
    Socket* m_socket;

    QLineEdit* m_portEdit;
    QLineEdit* m_ipEdit;
    QPlainTextEdit* m_displayTextEdit;
    QPlainTextEdit* m_inputTextEdit;
    QPushButton* m_sendBtn;
    QPushButton* m_connectBtn;

    void constructUI();
    void connectSlots();
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void onSendBtn();
    void onConnectBtn();
    void onDataReceived(const QString& msg);
};

#endif // WIDGET_H
