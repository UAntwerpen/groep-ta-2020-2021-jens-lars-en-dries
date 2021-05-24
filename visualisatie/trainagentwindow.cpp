#include "trainagentwindow.h"
#include "./ui_trainagentwindow.h"

TrainAgentWindow::TrainAgentWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TrainAgentWindow)
{
    ui->setupUi(this);
}

TrainAgentWindow::~TrainAgentWindow()
{
    delete ui;
}

void TrainAgentWindow::on_pushButton_clicked()
{

}

void TrainAgentWindow::on_pushButton_2_clicked()
{

}
