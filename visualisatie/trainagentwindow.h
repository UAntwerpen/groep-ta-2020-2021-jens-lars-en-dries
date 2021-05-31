#ifndef TRAINAGENTWINDOW_H
#define TRAINAGENTWINDOW_H

#include <QDialog>
#include <algorithms/QLearning.h>
#include <algorithms/MCLearning.h>

QT_BEGIN_NAMESPACE
namespace Ui { class TrainAgentWindow; }
QT_END_NAMESPACE

class TrainAgentWindow : public QDialog
{
    Q_OBJECT

public:
    TrainAgentWindow(QWidget *parent = nullptr);
    ~TrainAgentWindow();

    void setEnv(Environment *env);

    void setAgent(QLearning *agent);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TrainAgentWindow *ui;
    Environment* env = nullptr;
//    MCLearning agent = MCLearning(env, 0.1);
    QLearning* agent = nullptr;
};
#endif // TRAINAGENTWINDOW_H
