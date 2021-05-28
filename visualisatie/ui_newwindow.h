/********************************************************************************
** Form generated from reading UI file 'newwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWINDOW_H
#define UI_NEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NewWindow
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QCheckBox *checkBox;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *line;

    void setupUi(QDialog *NewWindow)
    {
        if (NewWindow->objectName().isEmpty())
            NewWindow->setObjectName(QString::fromUtf8("NewWindow"));
        NewWindow->resize(762, 376);
        lineEdit = new QLineEdit(NewWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 130, 31, 25));
        lineEdit_2 = new QLineEdit(NewWindow);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(110, 130, 31, 25));
        lineEdit_3 = new QLineEdit(NewWindow);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(170, 130, 61, 25));
        checkBox = new QCheckBox(NewWindow);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(630, 130, 121, 23));
        checkBox->setChecked(true);
        lineEdit_4 = new QLineEdit(NewWindow);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(270, 130, 31, 25));
        lineEdit_5 = new QLineEdit(NewWindow);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(380, 130, 31, 25));
        lineEdit_6 = new QLineEdit(NewWindow);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(520, 130, 31, 25));
        label = new QLabel(NewWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 100, 51, 17));
        label_2 = new QLabel(NewWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 100, 51, 17));
        label_3 = new QLabel(NewWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(180, 100, 51, 17));
        label_4 = new QLabel(NewWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(240, 100, 101, 17));
        label_5 = new QLabel(NewWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(360, 100, 101, 17));
        label_6 = new QLabel(NewWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(460, 100, 161, 17));
        label_7 = new QLabel(NewWindow);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(260, 20, 231, 61));
        label_8 = new QLabel(NewWindow);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(260, 190, 231, 61));
        label_9 = new QLabel(NewWindow);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(280, 270, 51, 17));
        label_10 = new QLabel(NewWindow);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(420, 270, 51, 17));
        label_11 = new QLabel(NewWindow);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(360, 270, 51, 17));
        lineEdit_7 = new QLineEdit(NewWindow);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(290, 310, 31, 25));
        lineEdit_8 = new QLineEdit(NewWindow);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(360, 310, 31, 25));
        lineEdit_9 = new QLineEdit(NewWindow);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(430, 310, 31, 25));
        pushButton = new QPushButton(NewWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 280, 89, 51));
        pushButton_2 = new QPushButton(NewWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(630, 280, 89, 51));
        line = new QFrame(NewWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 170, 731, 20));
        line->setAcceptDrops(true);
        line->setLineWidth(2);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(NewWindow);

        QMetaObject::connectSlotsByName(NewWindow);
    } // setupUi

    void retranslateUi(QDialog *NewWindow)
    {
        NewWindow->setWindowTitle(QApplication::translate("NewWindow", "NewWindow", nullptr));
        checkBox->setText(QApplication::translate("NewWindow", "deterministic", nullptr));
        label->setText(QApplication::translate("NewWindow", "<b>height<b>", nullptr));
        label_2->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">width</span></p></body></html>", nullptr));
        label_3->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">seed</span></p></body></html>", nullptr));
        label_4->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">living reward</span></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">end reward</span></p></body></html>", nullptr));
        label_6->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">percentage obstacles</span></p></body></html>", nullptr));
        label_7->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600; font-style:italic;\">New Environment</span></p></body></html>", nullptr));
        label_8->setText(QApplication::translate("NewWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; font-weight:600; font-style:italic;\">New Agent</span></p></body></html>", nullptr));
        label_9->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">epsilon</span></p></body></html>", nullptr));
        label_10->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">gamma</span></p><p><br/></p></body></html>", nullptr));
        label_11->setText(QApplication::translate("NewWindow", "<html><head/><body><p><span style=\" font-weight:600;\">alpha</span></p></body></html>", nullptr));
        pushButton->setText(QApplication::translate("NewWindow", "Cancel", nullptr));
        pushButton_2->setText(QApplication::translate("NewWindow", "Create", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewWindow: public Ui_NewWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWINDOW_H
