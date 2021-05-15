#include "mainwindow.h"
#include "world.h"
#include <iostream>
#include <QMessageBox>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new World;
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);

//    connect(scene,SIGNAL(clicked(int,int)),this,SLOT(clicked(int,int)));
    createActions();
    createMenus();
//    scene->removeAllMarking();  // Alle markeringen weg
//    scene->clearBoard(    );        // Alle stukken weg
//    g.setStartBord();
    this->update();
}


// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void MainWindow::clicked(int r, int k) {
//    if(lockmoves){
//        // Zorgt ervoor dat men niet meer verder kan spelen na een gelijkspel of schaakmat.
//        return;
//    }
//    if(this->selectFase()){
//        if(g.getMove_count() % 2 == 0 and g.getPiece(r, k)->getKleur() == wit){
//            scene->setTileSelect(r, k, true);
//            this->setSelectedPiece(g.getPiece(r, k));
//            if (display_moves->isChecked()) {
//                for(std::pair<int, int> move: g.getPiece(r, k)->geldige_zetten(g)){
//                    scene->setTileFocus(move.first, move.second, true);
//                }
//            }
//            if (display_kills->isChecked()) {
//                for(std::pair<int, int> move:  g.getPiece(r, k)->kwetsbare_zetten(g)){
//                    scene->setTileThreat(move.first, move.second, true);
//                }
//            }
//            this->selectToggle();
//            return;
//        } else if (g.getMove_count() % 2 == 1 and g.getPiece(r, k)->getKleur() == zwart){
//            scene->setTileSelect(r, k, true);
//            this->setSelectedPiece(g.getPiece(r, k));
//            if (display_moves->isChecked()) {
//                for(std::pair<int, int> move: g.getPiece(r, k)->geldige_zetten(g)){
//                    scene->setTileFocus(move.first, move.second, true);
//                }
//            }
//            if (display_kills->isChecked()) {
//                for(std::pair<int, int> move:  g.getPiece(r, k)->kwetsbare_zetten(g)){
//                    scene->setTileThreat(move.first, move.second, true);
//                }
//            }
//            this->selectToggle();
//            return;
//        }
//        return;
//    }
//    zw kleur = g.getMove_count()%2 == 0? zwart:wit;
//    this->selectToggle();
//    scene->removeAllTileSelection();
//    scene->removeAllTileFocus();
//    scene->removeAllTileDanger();
//    if(g.move(this->getSelectedPiece(), r, k)){
//        if(g.schaak(kleur)){
//            schaakPopup(kleur);
//        }
//        if(g.schaakmat(kleur)){
//            schaakmatPopup(kleur);
//            lockmoves = true;
//        }
//        if(g.pat(kleur)){
//            patPopup(kleur);
//            lockmoves = true;
//        }
//        if(g.getPromote()){
//            selectPromotion();
//        }
//        g.increaseMove_count();
//        scene->removeAllPieceThreats();
//        if (display_threats->isChecked()) {
//            for(std::pair<int, int> move: g.kwetsbare_schaakstukken(kleur)){
//                scene->setPieceThreat(move.first, move.second, true);
//            }
//        }
//    }
//    update();
}

void MainWindow::newGame()
{}

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

//void MainWindow::schaakPopup(zw kleur) {
//    QMessageBox box;
//    if(kleur == 0){
//        box.setText(QString("Zwart staat schaak!"));
//    }
//    else{
//        box.setText(QString("Wit staat schaak!"));
//    }
//    box.exec();
//}

//void MainWindow::schaakmatPopup(zw kleur) {
//    QMessageBox box;
//    if(kleur == 0){
//        box.setText(QString("Zwart staat schaakmat! Wit is de winnaar."));
//    }
//    else{
//        box.setText(QString("Wit staat schaakmat! Zwart is de winnaar."));
//    }
//    box.exec();
//}

//void MainWindow::patPopup(zw kleur) {
//    QMessageBox box;
//    if(kleur == 0){
//        box.setText(QString("Zwart staat pat! Gelijkspel."));
//    }
//    else{
//        box.setText(QString("Wit staat pat! Gelijkspel."));
//    }
//    box.exec();
//}

void MainWindow::undo() {
    QMessageBox box;
    box.setText(QString("Je hebt undo gekozen"));
    box.exec();
}

void MainWindow::redo() {}

void MainWindow::selectPromotion() {
//    QMessageBox box;
//    QPushButton Koningin;
//    Koningin.setText(QString("Koningin"));
//    connect(&Koningin, SIGNAL(clicked()), this, SLOT(pressKoningin()));
//    QPushButton Toren;
//    Toren.setText(QString("Toren"));
//    connect(&Toren, SIGNAL(clicked()), this, SLOT(pressToren()));
//    QPushButton Loper;
//    Loper.setText(QString("Loper"));
//    connect(&Loper, SIGNAL(clicked()), this, SLOT(pressLoper()));
//    QPushButton Paard;
//    Paard.setText(QString("Paard"));
//    connect(&Paard, SIGNAL(clicked()), this, SLOT(pressPaard()));
//    box.addButton(&Koningin, QMessageBox::YesRole);
//    box.addButton(&Toren, QMessageBox::YesRole);
//    box.addButton(&Loper, QMessageBox::YesRole);
//    box.addButton(&Paard, QMessageBox::YesRole);
//    box.setText(QString("Gelieve het schaakstuk aan te duiden naar waar u uw pion wilt promoveren: "));
//    box.exec();
}

void MainWindow::visualizationChange() {
    QMessageBox box;
    QString visstring = QString(display_moves->isChecked()?"T":"F")+(display_kills->isChecked()?"T":"F")+(display_threats->isChecked()?"T":"F");
    box.setText(QString("Visualization changed : ")+visstring);
    box.exec();
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void MainWindow::update() {
    scene->drawTile();
}





////////////////






void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Start a new game"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newGame);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read game from disk"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save game to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last move"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last undone move"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    display_moves= new QAction(tr("&valid moves"), this);
    display_moves->setStatusTip(tr("Show valid moves"));
    display_moves->setCheckable(true);
    display_moves->setChecked(true);
    connect(display_moves, &QAction::triggered, this, &MainWindow::visualizationChange);

    display_kills= new QAction(tr("threathed &enemy"), this);
    display_kills->setStatusTip(tr("Highlight threathened pieces (enemy)"));
    display_kills->setCheckable(true);
    display_kills->setChecked(true);
    connect(display_kills, &QAction::triggered, this, &MainWindow::visualizationChange);

    display_threats= new QAction(tr("threathed &player"), this);
    display_threats->setStatusTip(tr("Highlight threathened pieces (player)"));
    display_threats->setCheckable(true);
    display_threats->setChecked(true);
    connect(display_threats, &QAction::triggered, this, &MainWindow::visualizationChange);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(undoAct);
    gameMenu->addAction(redoAct);

    visualizeMenu = menuBar()->addMenu(tr("&Visualize"));
    visualizeMenu->addAction(display_moves);
    visualizeMenu->addAction(display_kills);
    visualizeMenu->addAction(display_threats);
}

void MainWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Spel verlaten"),
                                                  tr("Bent u zeker dat u het spel wil verlaten?\nNiet opgeslagen wijzigingen gaan verloren.")))
    {
        QApplication::quit();
    }
}

