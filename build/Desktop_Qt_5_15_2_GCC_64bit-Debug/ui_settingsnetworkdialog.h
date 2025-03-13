/********************************************************************************
** Form generated from reading UI file 'settingsnetworkdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSNETWORKDIALOG_H
#define UI_SETTINGSNETWORKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsNetworkDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_serverIp;
    QLineEdit *lineEdit_serverIp;
    QLabel *label_serverPort;
    QLineEdit *lineEdit_serverPort;
    QPushButton *pushButton_find;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_findIp;
    QLineEdit *lineEdit_findPort;
    QTextEdit *textEdit_messageTemplate;
    QGroupBox *group1;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButton_RX;
    QRadioButton *radioButton_TX;
    QRadioButton *radioButton_RXTX;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *group2;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButton_Log;
    QRadioButton *radioButton_Echo;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLineEdit *lineEdit_deviceTag;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_apply;

    void setupUi(QDialog *SettingsNetworkDialog)
    {
        if (SettingsNetworkDialog->objectName().isEmpty())
            SettingsNetworkDialog->setObjectName(QString::fromUtf8("SettingsNetworkDialog"));
        SettingsNetworkDialog->resize(400, 372);
        verticalLayout = new QVBoxLayout(SettingsNetworkDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_serverIp = new QLabel(SettingsNetworkDialog);
        label_serverIp->setObjectName(QString::fromUtf8("label_serverIp"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_serverIp);

        lineEdit_serverIp = new QLineEdit(SettingsNetworkDialog);
        lineEdit_serverIp->setObjectName(QString::fromUtf8("lineEdit_serverIp"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_serverIp);

        label_serverPort = new QLabel(SettingsNetworkDialog);
        label_serverPort->setObjectName(QString::fromUtf8("label_serverPort"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_serverPort);

        lineEdit_serverPort = new QLineEdit(SettingsNetworkDialog);
        lineEdit_serverPort->setObjectName(QString::fromUtf8("lineEdit_serverPort"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_serverPort);

        pushButton_find = new QPushButton(SettingsNetworkDialog);
        pushButton_find->setObjectName(QString::fromUtf8("pushButton_find"));

        formLayout->setWidget(3, QFormLayout::LabelRole, pushButton_find);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_findIp = new QLabel(SettingsNetworkDialog);
        label_findIp->setObjectName(QString::fromUtf8("label_findIp"));

        horizontalLayout_2->addWidget(label_findIp);

        lineEdit_findPort = new QLineEdit(SettingsNetworkDialog);
        lineEdit_findPort->setObjectName(QString::fromUtf8("lineEdit_findPort"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_findPort->sizePolicy().hasHeightForWidth());
        lineEdit_findPort->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_findPort);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_2);

        textEdit_messageTemplate = new QTextEdit(SettingsNetworkDialog);
        textEdit_messageTemplate->setObjectName(QString::fromUtf8("textEdit_messageTemplate"));

        formLayout->setWidget(6, QFormLayout::SpanningRole, textEdit_messageTemplate);

        group1 = new QGroupBox(SettingsNetworkDialog);
        group1->setObjectName(QString::fromUtf8("group1"));
        horizontalLayout_4 = new QHBoxLayout(group1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioButton_RX = new QRadioButton(group1);
        radioButton_RX->setObjectName(QString::fromUtf8("radioButton_RX"));

        horizontalLayout_4->addWidget(radioButton_RX);

        radioButton_TX = new QRadioButton(group1);
        radioButton_TX->setObjectName(QString::fromUtf8("radioButton_TX"));

        horizontalLayout_4->addWidget(radioButton_TX);

        radioButton_RXTX = new QRadioButton(group1);
        radioButton_RXTX->setObjectName(QString::fromUtf8("radioButton_RXTX"));

        horizontalLayout_4->addWidget(radioButton_RXTX);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        formLayout->setWidget(4, QFormLayout::SpanningRole, group1);

        group2 = new QGroupBox(SettingsNetworkDialog);
        group2->setObjectName(QString::fromUtf8("group2"));
        horizontalLayout_5 = new QHBoxLayout(group2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        radioButton_Log = new QRadioButton(group2);
        radioButton_Log->setObjectName(QString::fromUtf8("radioButton_Log"));

        horizontalLayout_5->addWidget(radioButton_Log);

        radioButton_Echo = new QRadioButton(group2);
        radioButton_Echo->setObjectName(QString::fromUtf8("radioButton_Echo"));

        horizontalLayout_5->addWidget(radioButton_Echo);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        formLayout->setWidget(5, QFormLayout::SpanningRole, group2);

        label = new QLabel(SettingsNetworkDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_deviceTag = new QLineEdit(SettingsNetworkDialog);
        lineEdit_deviceTag->setObjectName(QString::fromUtf8("lineEdit_deviceTag"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_deviceTag);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_apply = new QPushButton(SettingsNetworkDialog);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));

        horizontalLayout->addWidget(pushButton_apply);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SettingsNetworkDialog);

        QMetaObject::connectSlotsByName(SettingsNetworkDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsNetworkDialog)
    {
        SettingsNetworkDialog->setWindowTitle(QCoreApplication::translate("SettingsNetworkDialog", "Dialog", nullptr));
        label_serverIp->setText(QCoreApplication::translate("SettingsNetworkDialog", "serverIp", nullptr));
        label_serverPort->setText(QCoreApplication::translate("SettingsNetworkDialog", "serverPort", nullptr));
        pushButton_find->setText(QCoreApplication::translate("SettingsNetworkDialog", "FindByPort", nullptr));
        label_findIp->setText(QCoreApplication::translate("SettingsNetworkDialog", "deviceIp", nullptr));
        group1->setTitle(QCoreApplication::translate("SettingsNetworkDialog", "Filter", nullptr));
        radioButton_RX->setText(QCoreApplication::translate("SettingsNetworkDialog", "RX", nullptr));
        radioButton_TX->setText(QCoreApplication::translate("SettingsNetworkDialog", "TX", nullptr));
        radioButton_RXTX->setText(QCoreApplication::translate("SettingsNetworkDialog", "RXTX", nullptr));
        group2->setTitle(QCoreApplication::translate("SettingsNetworkDialog", "Mode", nullptr));
        radioButton_Log->setText(QCoreApplication::translate("SettingsNetworkDialog", "Log", nullptr));
        radioButton_Echo->setText(QCoreApplication::translate("SettingsNetworkDialog", "Echo", nullptr));
        label->setText(QCoreApplication::translate("SettingsNetworkDialog", "DeviceTag", nullptr));
        pushButton_apply->setText(QCoreApplication::translate("SettingsNetworkDialog", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsNetworkDialog: public Ui_SettingsNetworkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSNETWORKDIALOG_H
