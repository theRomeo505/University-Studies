/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QTimeEdit *time_current;
    QListWidget *listWidget_timer;
    QListWidget *listWidget_clocks;
    QCheckBox *checkBox;
    QProgressBar *progressBar;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(926, 391);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(220, 290, 75, 23));
        time_current = new QTimeEdit(centralwidget);
        time_current->setObjectName(QString::fromUtf8("time_current"));
        time_current->setGeometry(QRect(80, 190, 118, 22));
        time_current->setCurrentSectionIndex(0);
        listWidget_timer = new QListWidget(centralwidget);
        listWidget_timer->setObjectName(QString::fromUtf8("listWidget_timer"));
        listWidget_timer->setGeometry(QRect(405, 40, 161, 192));
        listWidget_clocks = new QListWidget(centralwidget);
        listWidget_clocks->setObjectName(QString::fromUtf8("listWidget_clocks"));
        listWidget_clocks->setGeometry(QRect(700, 80, 171, 192));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(60, 290, 121, 17));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(90, 40, 118, 23));
        progressBar->setValue(0);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 90, 121, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 130, 131, 21));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(110, 231, 69, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 240, 47, 13));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(460, 20, 47, 13));
        label_4->setTextFormat(Qt::AutoText);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(750, 20, 71, 16));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 110, 91, 23));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(250, 140, 91, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 926, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        listWidget_timer->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        time_current->setDisplayFormat(QCoreApplication::translate("MainWindow", "H:mm:ss", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "do not disturb", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Number of timers: 0", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Fastest timer \342\204\2260", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "default", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "secret", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Sound:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Timers", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Alarm Clocks", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Start/unpause", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
