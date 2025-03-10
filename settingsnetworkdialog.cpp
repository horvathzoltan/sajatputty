#include "settingsnetworkdialog.h"
#include "ui_settingsnetworkdialog.h"

#include <helpers/networkhelper.h>

//#include "infrastructure/globals.h"


//Globals _globals;

SettingsNetworkDialog::SettingsNetworkDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsNetworkDialog)
{
    ui->setupUi(this);

}

SettingsNetworkDialog::~SettingsNetworkDialog()
{
    delete ui;
}


void SettingsNetworkDialog::on_pushButton_apply_clicked()
{

    _currentSettings = GetSettings();
    emit apply();
    hide();
}

void SettingsNetworkDialog::WriteSettings(const NetworkSettingsVM& p)
{
    _currentSettings = p;

    ui->lineEdit_serverIp->setText(p.serverIp);
    ui->lineEdit_serverPort->setText(QString::number(p.serverPort));
    ui->textEdit_messageTemplate->setPlainText(p.messageTemplate);

    ui->lineEdit_findPort->setText(QString::number(p.serverPort));
    ui->label_findIp->setText(p.deviceIp);
}

NetworkSettingsVM SettingsNetworkDialog::GetSettings()
{
    NetworkSettingsVM m;

    m.serverIp = ui->lineEdit_serverIp->text();
    bool ok;
    int port = ui->lineEdit_serverPort->text().toInt(&ok);
    m.serverPort = ok?port:-1;
    m.messageTemplate = ui->textEdit_messageTemplate->toPlainText();
    return m;
}

void SettingsNetworkDialog::on_pushButton_find_clicked()
{
    ui->pushButton_find->setEnabled(false);
    ui->pushButton_apply->setEnabled(false);
    ui->lineEdit_serverIp->setEnabled(false);
    ui->lineEdit_serverPort->setEnabled(false);

    ui->pushButton_find->repaint();
    ui->pushButton_apply->repaint();
    ui->lineEdit_serverIp->repaint();
    ui->lineEdit_serverPort->repaint();
    //SettingsNetworkDialog::SettingsNetworkVM m = GetSettings();

    QString serverIp = ui->label_findIp->text();
    bool ok;
    int serverPort = ui->lineEdit_findPort->text().toInt(&ok);
    if(ok)
    {
        QStringList hosts = NetworkHelper::FindHosts_ByPorts(serverIp, {serverPort});

        if(hosts.count()==1)
        {
            ui->lineEdit_serverIp->setText(hosts.first());
            ui->lineEdit_serverPort->setText(QString::number(serverPort));
        }
    }
    ui->pushButton_find->setEnabled(true);
    ui->pushButton_apply->setEnabled(true);
    ui->lineEdit_serverIp->setEnabled(true);
    ui->lineEdit_serverPort->setEnabled(true);
}

