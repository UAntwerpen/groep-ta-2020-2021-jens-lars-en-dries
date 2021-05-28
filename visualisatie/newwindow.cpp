#include "newwindow.h"
#include "./ui_newwindow.h"

NewWindow::NewWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewWindow)
{
    ui->setupUi(this);
}

NewWindow::~NewWindow()
{
    delete ui;
    w = nullptr;
}


void NewWindow::on_pushButton_clicked()
{
    QDialog::done(0);
}

void NewWindow::on_pushButton_2_clicked()
{
    Environment* tempEnv = new Environment(ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt(),
                                           ui->lineEdit_3->text().toInt(), ui->checkBox->isChecked(),
                                           ui->lineEdit_4->text().toFloat(), ui->lineEdit_5->text().toFloat(),
                                           ui->lineEdit_6->text().toFloat());
    QLearning* tempAgent = new QLearning(tempEnv, ui->lineEdit_7->text().toFloat(), ui->lineEdit_8->text().toFloat(), ui->lineEdit_9->text().toFloat());
    w->scene->setEnv(*tempEnv);
    w->scene->agent = *tempAgent;
    QDialog::done(0);
}

void NewWindow::setW(MainWindow *w) {
    NewWindow::w = w;
}
