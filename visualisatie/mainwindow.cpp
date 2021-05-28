#include "mainwindow.h"
#include "../parser/LAParser.h"
#include "world.h"
#include <iostream>
#include "../datastructures/Environment.h"
#include "../parser/EnvironmentParser.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "trainagentwindow.h"
#include "newwindow.h"

#include <QMessageBox>
#include <QtWidgets>
#include <QTextStream>

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->showMaximized();
    scene = new World;
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);
    EnvironmentParser S;
    S.loadFile("data/testEnv.xml");
    Environment* env = S.parseFile();
    scene->setEnv(*env);
    LA* parse_test = new LA();
    LAParser Q;
    Q.loadFile("data/testLA.xml");
    Q.parseFile(parse_test);
    scene->updateAgent(parse_test);

    createActions();
    createMenus();
    scene->drawWorld();
}

void MainWindow::newGame()
{
    NewWindow y;
    y.setW(this);
    y.exec();
    scene->refreshWorld();
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);
}

void MainWindow::save() {
//    QString fileName = QFileDialog::getSaveFileName(this,
//                                                    tr("Save game"), "",
//                                                    tr("Chess File (*.chs);;All Files (*)"));
//
//    if (fileName.isEmpty())
//        return;
//    else {
//        QFile file(fileName);
//        if (!file.open(QIODevice::WriteOnly)) {
//            QMessageBox::information(this, tr("Unable to open file"),
//                                     file.errorString());
//            return;
//        }
//        QDataStream out(&file);
//        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
//        for  (int i=0;i<8;i++) {
//            out << QString("Pb");
//        }
//        for  (int r=3;r<7;r++) {
//            for (int k=0;k<8;k++) {
//                out << QString(".");
//            }
//        }
//        for  (int i=0;i<8;i++) {
//            out << QString("Pw");
//        }
//        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
//    }
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load game"), "",
                                                    tr("Chess File (*.chs);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Error reading file "+fileName);
                    }
                }
                debugstring += "\n";
            }
            QMessageBox::information(this, tr("Debug"),
                                     debugstring);
        } catch (QString& Q) {
            QMessageBox::information(this, tr("Error reading file"),
                                     Q);
        }
    }
    update();
}

void MainWindow::train() {
    TrainAgentWindow x;
    x.setEnv(&scene->env);
    x.setAgent(&scene->agent);
    if(x.exec() == 0){
        scene->refreshWorld();
        scene->drawPierePath();
    }
}

void MainWindow::visualizationChange() {
    scene->togglePolicy();
    scene->refreshWorld();
}

void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new Environment and Agent."));
    connect(newAct, &QAction::triggered, this, &MainWindow::newGame);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read data from disk"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save data to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    trainAgent = new QAction(tr("&train"), this);
    trainAgent->setStatusTip(tr("start a training"));
    connect(trainAgent, &QAction::triggered, this, &MainWindow::train);

    display_policy= new QAction(tr("&policy"), this);
    display_policy->setStatusTip(tr("Show policy"));
    display_policy->setCheckable(true);
    display_policy->setChecked(false);
    connect(display_policy, &QAction::triggered, this, &MainWindow::visualizationChange);

}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&General"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(trainAgent);

    visualizeMenu = menuBar()->addMenu(tr("&Visualize"));
    visualizeMenu->addAction(display_policy);
}

void MainWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Spel verlaten"),
                                                  tr("Bent u zeker dat u het spel wil verlaten?\nNiet opgeslagen wijzigingen gaan verloren.")))
    {
        QApplication::quit();
    }
}


