#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingdialog.h"

#include <QwebFrame.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString html =
            "<head><script type=\"text/javascript\">"
            "window.onload = function()"
            "{"
            "    document.getElementById(\"quit\").onmousedown = function()"
            "    {"
            "        alert('quit');"
            "        Qt.quit();"
            "    };"
            "};"
            "function addIrcMessage(msg)"
            "{"
            "    var element = document.createElement('div');"
            "    element.id = \"id\";"
            "    element.innerHTML = msg;"
            "    element.style.backgroundColor = 'red';"
            "    document.getElementById(\"ircmessage\").appendChild(element);"
            "}"
            "function addIrcChannel(channelName)"
            "{"
            "    var element = document.createElement('div');"
            "    element.id = \"id\";"
            "    element.innerHTML = channelName;"
            "    element.style.backgroundColor = 'green';"
            "    document.getElementById(\"ircchannel\").appendChild(element);"
            "}"
            "</script></head>"
            "<body>"
            "        <div id=\"ircchannel\">ircchannel</div>"
            "        <div id=\"ircmessage\">ircmessage</div>"
            "        <input type=\"input\" id=\"input_text\">"
            "        <input type=\"button\" value=\"hoge\" onclick='javascript:addIrcMessage(input_text.value); myoperations.submit(input_text.value);'>"
            "        <a id=\"quit\">X</a>"
            "</body>"
            "";
    ui->mainWebView->setHtml(html);

    client = new Client(this);

    QWebFrame* frame = ui->mainWebView->page()->mainFrame();
    frame->evaluateJavaScript("addIrcMessage('a');");
    frame->addToJavaScriptWindowObject("myoperations", new MyJavaScriptOperations(client));
//    frame->evaluateJavaScript("addIrcChannel('ttt');");
    connect(client, SIGNAL(addMessage(IRCMessage)), this, SLOT(addIrcMessage(IRCMessage)));
    connect(client, SIGNAL(addChannel(IRCChannel)), this, SLOT(addIrcChannel(IRCChannel)));

    client->connectToServer();
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}

void MainWindow::addIrcMessage(IRCMessage message)
{
    QString str = message.nick + ": " + message.msg;
    ui->mainWebView->page()->mainFrame()->evaluateJavaScript("addIrcMessage('" + str + "');");
}

void MainWindow::addIrcChannel(IRCChannel channel)
{
    ui->mainWebView->page()->mainFrame()->evaluateJavaScript("addIrcChannel('" + channel.name + "');");
}

void MainWindow::on_mainLineEdit_returnPressed()
{
    const QString msg = this->ui->mainLineEdit->text();
    qDebug("%s", qPrintable(msg));

    IRCMessage ircMsg;
    ircMsg.channel = "testha";
    ircMsg.msg = msg;

    client->sendMessage(ircMsg);

    this->ui->mainLineEdit->setText("");
    this->addIrcMessage(ircMsg);
}

void MainWindow::on_actionSettings_triggered()
{
    SettingDialog sd;
    int ret = sd.exec();
    qDebug("%d", ret);
    /*
    Ui::SettingDialog *dlg = new Ui::SettingDialog();
    dlg->show();
    //settingDialog
    dlg->setupUi(settingDialog);
//    dlg.setupUi(settingDialog);
    settingDialog->exec();
//    QDialog qd;
//   dlg.setupUi();
*/
}
