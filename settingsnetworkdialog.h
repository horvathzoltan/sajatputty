#ifndef SETTINGSNETWORKDIALOG_H
#define SETTINGSNETWORKDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsNetworkDialog;
}

class SettingsNetworkDialog : public QDialog
{
    Q_OBJECT

public:
    struct SettingsNetworkVM {
        QString deviceIp;
        QString serverIp;
        int serverPort;
        QString messageTemplate;
    };


    explicit SettingsNetworkDialog(QWidget *parent = nullptr);
    ~SettingsNetworkDialog();

    SettingsNetworkVM settings(){return _currentSettings;}
    void WriteSettings(const SettingsNetworkVM &);


private slots:
    void on_pushButton_apply_clicked();

    void on_pushButton_find_clicked();

signals:
    void apply();

private:
    Ui::SettingsNetworkDialog *ui;
    SettingsNetworkVM _currentSettings;

    SettingsNetworkVM GetSettings();
};

#endif // SETTINGSNETWORKDIALOG_H
