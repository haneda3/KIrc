#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "ircmessage.h"

namespace Ui {
class MainWindow;
}

class MyJavaScriptOperations : public QObject {
    Q_OBJECT
private:
//    QWebView* _webView;
    Client* _client;
public:
    MyJavaScriptOperations(Client* client){
        qDebug() << "In constructor";
        _client = client;
    }

    Q_INVOKABLE void submit(QString message)
    {
//        QVariant f1result = _webView->page()->mainFrame()->evaluateJavaScript("test()");
//        qDebug() << f1result.toString();
        IRCMessage ircMsg;
        ircMsg.channel = "testha";
        ircMsg.msg = message;
        _client->sendMessage(ircMsg);

        qDebug("%s", qPrintable(message));
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Client* client;

public slots:
    void addIrcMessage(IRCMessage message);
    void addIrcChannel(IRCChannel channel);
private slots:
    void on_mainLineEdit_returnPressed();
    void on_actionSettings_triggered();
};

#endif // MAINWINDOW_H
