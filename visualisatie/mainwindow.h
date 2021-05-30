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
    World *scene;

private slots:
    void newGame();
    void train();
    void visualizationChange();

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
    QAction *trainAgent;
    QAction *exitAct;

    QAction* display_policy;
};



#endif //TO_GROEP_MAINWINDOW_H
