#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    QSettings settings;

    QString host = settings.value("server/host", "example.com").toString();
    QString port = settings.value("server/port", "6666").toString();
    QString nick = settings.value("server/nick", "nanashi").toString();

    ui->editServer->setText(host);
    ui->editPort->setText(port);
    ui->editNick->setText(nick);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_buttonBox_accepted()
{
    QString host = ui->editServer->text();
    QString port = ui->editPort->text();
    QString nick = ui->editNick->text();

    QSettings settings;
    settings.setValue("server/host", host);
    settings.setValue("server/port", port);
    settings.setValue("server/nick", nick);
}
