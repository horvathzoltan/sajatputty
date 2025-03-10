#ifndef SETTINGSNETWORKDIALOG_H
#define SETTINGSNETWORKDIALOG_H

#include "viewmodels/networksettingsvm.h"
#include <QDialog>

namespace Ui {
class SettingsNetworkDialog;
}

class SettingsNetworkDialog : public QDialog
{
    Q_OBJECT

public:



    explicit SettingsNetworkDialog(QWidget *parent = nullptr);
    ~SettingsNetworkDialog();

    NetworkSettingsVM settings(){return _currentSettings;}
    void WriteSettings(const NetworkSettingsVM &);


private slots:
    void on_pushButton_apply_clicked();

    void on_pushButton_find_clicked();

signals:
    void apply();

private:
    Ui::SettingsNetworkDialog *ui;
    NetworkSettingsVM _currentSettings;

    NetworkSettingsVM GetSettings();
};

#endif // SETTINGSNETWORKDIALOG_H
