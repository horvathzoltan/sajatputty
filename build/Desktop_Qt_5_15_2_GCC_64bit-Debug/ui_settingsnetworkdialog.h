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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
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
    QLabel *label_serverPort;
    QTextEdit *textEdit_messageTemplate;
    QPushButton *pushButton_find;
    QLineEdit *lineEdit_serverIp;
    QLineEdit *lineEdit_serverPort;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_findIp;
    QLineEdit *lineEdit_findPort;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_apply;

    void setupUi(QDialog *SettingsNetworkDialog)
    {
        if (SettingsNetworkDialog->objectName().isEmpty())
            SettingsNetworkDialog->setObjectName(QString::fromUtf8("SettingsNetworkDialog"));
        SettingsNetworkDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(SettingsNetworkDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_serverIp = new QLabel(SettingsNetworkDialog);
        label_serverIp->setObjectName(QString::fromUtf8("label_serverIp"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_serverIp);

        label_serverPort = new QLabel(SettingsNetworkDialog);
        label_serverPort->setObjectName(QString::fromUtf8("label_serverPort"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_serverPort);

        textEdit_messageTemplate = new QTextEdit(SettingsNetworkDialog);
        textEdit_messageTemplate->setObjectName(QString::fromUtf8("textEdit_messageTemplate"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, textEdit_messageTemplate);

        pushButton_find = new QPushButton(SettingsNetworkDialog);
        pushButton_find->setObjectName(QString::fromUtf8("pushButton_find"));

        formLayout->setWidget(2, QFormLayout::LabelRole, pushButton_find);

        lineEdit_serverIp = new QLineEdit(SettingsNetworkDialog);
        lineEdit_serverIp->setObjectName(QString::fromUtf8("lineEdit_serverIp"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_serverIp);

        lineEdit_serverPort = new QLineEdit(SettingsNetworkDialog);
        lineEdit_serverPort->setObjectName(QString::fromUtf8("lineEdit_serverPort"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_serverPort);

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


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);


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
        pushButton_apply->setText(QCoreApplication::translate("SettingsNetworkDialog", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsNetworkDialog: public Ui_SettingsNetworkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSNETWORKDIALOG_H
