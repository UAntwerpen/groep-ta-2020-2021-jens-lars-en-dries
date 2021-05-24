#ifndef TRAINAGENTWINDOW_H
#define TRAINAGENTWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TrainAgentWindow; }
QT_END_NAMESPACE

class TrainAgentWindow : public QDialog
{
    Q_OBJECT

public:
    TrainAgentWindow(QWidget *parent = nullptr);
    ~TrainAgentWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TrainAgentWindow *ui;
};
#endif // TRAINAGENTWINDOW_H
