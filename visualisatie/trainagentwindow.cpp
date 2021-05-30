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
    env = nullptr;
    agent = nullptr;
    delete ui;
}

void TrainAgentWindow::on_pushButton_clicked()
{
    QDialog::done(1);
}

void TrainAgentWindow::on_pushButton_2_clicked()
{
    int i = ui->lineEdit_3->text().toInt();
    if(i <= 0){
        i = 200;
    }
    agent->train(*env, ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt(), i);
    QDialog::done(0);

}

void TrainAgentWindow::setEnv(Environment *env) {
    TrainAgentWindow::env = env;
}

void TrainAgentWindow::setAgent(QLearning *agent) {
    TrainAgentWindow::agent = agent;
}
