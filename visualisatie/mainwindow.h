#ifndef TO_GROEP_MAINWINDOW_H
#define TO_GROEP_MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <iostream>
#include "world.h"
#include "trainagentwindow.h"

class QSettings;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void update();
    bool selectFase() {return policy_flag;}
    void selectToggle() { policy_flag = !policy_flag && true;}


private:
    World *scene;
    bool policy_flag = true;

private slots:
    void clicked(int x, int y);
    void newGame();
    void open();
    void save();
    void undo();
    void train();
    void visualizationChange();

    // De volgende lijnen kunnen genegeerd worden voor de opdracht

    void on_actionExit_triggered();
    void closeEvent (QCloseEvent *event)
    {
        on_actionExit_triggered();
        event->ignore();
    }

private:
    void createActions();
    void createMenus();
    QMenu *fileMenu;
    QMenu *gameMenu;
    QMenu *visualizeMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *undoAct;
    QAction *trainAgent;
    QAction *exitAct;

    QAction* display_policy;
};



#endif //TO_GROEP_MAINWINDOW_H
