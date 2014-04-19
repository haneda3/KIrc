#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "ircmessage.h"

namespace Ui {
class MainWindow;
}

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
private slots:
    void on_mainLineEdit_returnPressed();
    void on_actionSettings_triggered();
};

#endif // MAINWINDOW_H
