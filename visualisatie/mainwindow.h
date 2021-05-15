#ifndef TO_GROEP_MAINWINDOW_H
#define TO_GROEP_MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <iostream>
#include "world.h"

class QSettings;

// Toevoeging methodes ivm bepalen of we moeten selecteren of niet, toevoeging methodes ivm de verscheidene QuestionBoxes

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void update();
    bool selectFase() {return select_flag;}
    void selectToggle() {select_flag = !select_flag && true;}
//    void setSelectedPiece(SchaakStuk* s){selected_piece = s;}
//    SchaakStuk* getSelectedPiece(){return selected_piece;}
    void selectPromotion();
//    void schaakPopup(zw kleur);
//    void schaakmatPopup(zw kleur);
//    void patPopup(zw kleur);

private:
    World *scene;
//    Game g;
//    SchaakStuk* selected_piece;
    bool select_flag = true;
    bool lockmoves = false;

private slots:
    void clicked(int x, int y);
    void newGame();
    void open();
    void save();
    void undo();
    void redo();
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
    QAction *redoAct;
    QAction *exitAct;

    QAction* display_moves;
    QAction* display_kills;
    QAction* display_threats;
};



#endif //TO_GROEP_MAINWINDOW_H
