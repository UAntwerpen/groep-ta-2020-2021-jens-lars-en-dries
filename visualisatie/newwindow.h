#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QDialog>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NewWindow; }
QT_END_NAMESPACE

class NewWindow : public QDialog
{
    Q_OBJECT
public:
    void setW(MainWindow *w);

public:
    NewWindow(QWidget *parent = nullptr);
    ~NewWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NewWindow *ui;
    MainWindow* w  = nullptr;
};
#endif // NEWWINDOW_H
