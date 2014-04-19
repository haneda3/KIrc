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
            "}</script></head>"
            "<body>"
            "        <div id=\"ircmessage\">ircmessage</div>"
            "        <input type=\"button\" value=\"hoge\" onclick='javascript:addIrcMessage(\"a\");'>"
            "        <a id=\"quit\">X</a>"
            "</body>"
            "";
    ui->mainWebView->setHtml(html);

    QWebFrame* frame = ui->mainWebView->page()->mainFrame();
    frame->evaluateJavaScript("addIrcMessage('a');");

    client = new Client(this);

    connect(client, SIGNAL(addMessage(IRCMessage)), this, SLOT(addIrcMessage(IRCMessage)));

    client->connectToServer();
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}

void MainWindow::addIrcMessage(IRCMessage message)
{
    QString str = message.msg;
    ui->mainWebView->page()->mainFrame()->evaluateJavaScript("addIrcMessage('" + str + "');");
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
