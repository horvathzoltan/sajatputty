/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionClear;
    QAction *actionQuit;
    QAction *actionLoadSession;
    QAction *actionSaveSession;
    QAction *actionLoadSettings;
    QAction *actionSaveSettings;
    QAction *actionConfigure_Network;
    QAction *actionLoadSettings_Network;
    QAction *actionSaveSettings_Network;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon2);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        actionLoadSession = new QAction(MainWindow);
        actionLoadSession->setObjectName(QString::fromUtf8("actionLoadSession"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadSession->setIcon(icon5);
        actionLoadSession->setMenuRole(QAction::TextHeuristicRole);
        actionSaveSession = new QAction(MainWindow);
        actionSaveSession->setObjectName(QString::fromUtf8("actionSaveSession"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveSession->setIcon(icon6);
        actionSaveSession->setMenuRole(QAction::TextHeuristicRole);
        actionLoadSettings = new QAction(MainWindow);
        actionLoadSettings->setObjectName(QString::fromUtf8("actionLoadSettings"));
        actionLoadSettings->setIcon(icon5);
        actionLoadSettings->setMenuRole(QAction::TextHeuristicRole);
        actionSaveSettings = new QAction(MainWindow);
        actionSaveSettings->setObjectName(QString::fromUtf8("actionSaveSettings"));
        actionSaveSettings->setIcon(icon6);
        actionSaveSettings->setMenuRole(QAction::TextHeuristicRole);
        actionConfigure_Network = new QAction(MainWindow);
        actionConfigure_Network->setObjectName(QString::fromUtf8("actionConfigure_Network"));
        actionConfigure_Network->setIcon(icon2);
        actionLoadSettings_Network = new QAction(MainWindow);
        actionLoadSettings_Network->setObjectName(QString::fromUtf8("actionLoadSettings_Network"));
        actionLoadSettings_Network->setIcon(icon5);
        actionLoadSettings_Network->setMenuRole(QAction::TextHeuristicRole);
        actionSaveSettings_Network = new QAction(MainWindow);
        actionSaveSettings_Network->setObjectName(QString::fromUtf8("actionSaveSettings_Network"));
        actionSaveSettings_Network->setIcon(icon6);
        actionSaveSettings_Network->setMenuRole(QAction::TextHeuristicRole);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addAction(actionLoadSettings);
        mainToolBar->addAction(actionSaveSettings);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionConfigure_Network);
        mainToolBar->addAction(actionLoadSettings_Network);
        mainToolBar->addAction(actionSaveSettings_Network);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionClear);
        mainToolBar->addAction(actionLoadSession);
        mainToolBar->addAction(actionSaveSession);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Simple Terminal", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
#if QT_CONFIG(tooltip)
        actionAbout->setToolTip(QCoreApplication::translate("MainWindow", "About program", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionAbout->setShortcut(QCoreApplication::translate("MainWindow", "Alt+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAboutQt->setText(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "C&onnect", nullptr));
#if QT_CONFIG(tooltip)
        actionConnect->setToolTip(QCoreApplication::translate("MainWindow", "Connect to serial port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionConnect->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "&Disconnect", nullptr));
#if QT_CONFIG(tooltip)
        actionDisconnect->setToolTip(QCoreApplication::translate("MainWindow", "Disconnect from serial port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDisconnect->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionConfigure->setText(QCoreApplication::translate("MainWindow", "&Configure", nullptr));
#if QT_CONFIG(tooltip)
        actionConfigure->setToolTip(QCoreApplication::translate("MainWindow", "Configure serial port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionConfigure->setShortcut(QCoreApplication::translate("MainWindow", "Alt+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClear->setText(QCoreApplication::translate("MainWindow", "C&lear", nullptr));
#if QT_CONFIG(tooltip)
        actionClear->setToolTip(QCoreApplication::translate("MainWindow", "Clear data", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("MainWindow", "Alt+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoadSession->setText(QCoreApplication::translate("MainWindow", "LoadSession", nullptr));
#if QT_CONFIG(tooltip)
        actionLoadSession->setToolTip(QCoreApplication::translate("MainWindow", "Load session", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveSession->setText(QCoreApplication::translate("MainWindow", "SaveSession", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveSession->setToolTip(QCoreApplication::translate("MainWindow", "Save session", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLoadSettings->setText(QCoreApplication::translate("MainWindow", "LoadSettings", nullptr));
#if QT_CONFIG(tooltip)
        actionLoadSettings->setToolTip(QCoreApplication::translate("MainWindow", "Load settings", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveSettings->setText(QCoreApplication::translate("MainWindow", "SaveSettings", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveSettings->setToolTip(QCoreApplication::translate("MainWindow", "Save settings", nullptr));
#endif // QT_CONFIG(tooltip)
        actionConfigure_Network->setText(QCoreApplication::translate("MainWindow", "&ConfigureNetwork", nullptr));
#if QT_CONFIG(tooltip)
        actionConfigure_Network->setToolTip(QCoreApplication::translate("MainWindow", "Configure network", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionConfigure_Network->setShortcut(QCoreApplication::translate("MainWindow", "Shift+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoadSettings_Network->setText(QCoreApplication::translate("MainWindow", "LoadNetworkSettings", nullptr));
#if QT_CONFIG(tooltip)
        actionLoadSettings_Network->setToolTip(QCoreApplication::translate("MainWindow", "Load network settings", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveSettings_Network->setText(QCoreApplication::translate("MainWindow", "SaveSettings_Network", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveSettings_Network->setToolTip(QCoreApplication::translate("MainWindow", "Save network settings", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
