/********************************************************************************
** Form generated from reading UI file 'trainagentwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAINAGENTWINDOW_H
#define UI_TRAINAGENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrainAgentWindow
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *TrainAgentWindow)
    {
        if (TrainAgentWindow->objectName().isEmpty())
            TrainAgentWindow->setObjectName(QString::fromUtf8("TrainAgentWindow"));
        TrainAgentWindow->resize(718, 224);
        lineEdit = new QLineEdit(TrainAgentWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(40, 100, 113, 25));
        lineEdit_2 = new QLineEdit(TrainAgentWindow);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(300, 100, 113, 25));
        lineEdit_3 = new QLineEdit(TrainAgentWindow);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(560, 100, 113, 25));
        label = new QLabel(TrainAgentWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 70, 111, 20));
        label_2 = new QLabel(TrainAgentWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 70, 221, 21));
        label_3 = new QLabel(TrainAgentWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(530, 60, 171, 21));
        pushButton = new QPushButton(TrainAgentWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(240, 170, 89, 25));
        pushButton_2 = new QPushButton(TrainAgentWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(380, 170, 89, 25));
        label_4 = new QLabel(TrainAgentWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 20, 571, 20));
        label_5 = new QLabel(TrainAgentWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(580, 80, 91, 20));

        retranslateUi(TrainAgentWindow);

        QMetaObject::connectSlotsByName(TrainAgentWindow);
    } // setupUi

    void retranslateUi(QWidget *TrainAgentWindow)
    {
        TrainAgentWindow->setWindowTitle(QApplication::translate("TrainAgentWindow", "TrainAgentWindow", nullptr));
        label->setText(QApplication::translate("TrainAgentWindow", "Aantal Episodes", nullptr));
        label_2->setText(QApplication::translate("TrainAgentWindow", "Maximum stappen per Episode", nullptr));
        label_3->setText(QApplication::translate("TrainAgentWindow", "Console print per Epoch", nullptr));
        pushButton->setText(QApplication::translate("TrainAgentWindow", "Annuleer", nullptr));
        pushButton_2->setText(QApplication::translate("TrainAgentWindow", "Train", nullptr));
        label_4->setText(QApplication::translate("TrainAgentWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Gelieve volgende waarden in te vullen en vervolgens op de train knop te duwen.</span></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("TrainAgentWindow", "( optioneel)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrainAgentWindow: public Ui_TrainAgentWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAINAGENTWINDOW_H
