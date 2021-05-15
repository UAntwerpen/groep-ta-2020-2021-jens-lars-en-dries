#include "world.h"

#include <QtWidgets>
#include <QPixmap>

World::World(QObject* parent ): QGraphicsScene(parent){
    cGrassColor = Qt::green;
    cWaterColor = Qt::blue;

    cBlockSize = 30;
}

void World::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    QPointF scenePos = mouseEvent->scenePos();
    if( scenePos.x() < 0 || scenePos.y() < 0 || scenePos.x() > 8 || scenePos.y() > 8 )
    {
        focusRow = -1;
        focusCol = -1;
        return;
    }

    focusRow = scenePos.y();
    focusCol = scenePos.x();

    if (focusRow>=0 && focusRow<8 && focusCol>=0 && focusCol<8) {
        emit(clicked((int) focusRow, (int) focusCol));
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void World::drawTile(){
    for(int i = 1; i < 6; i++){
        for(int j = 1 ; j < 6; j++){
            QGraphicsRectItem *rect = new QGraphicsRectItem( i*cBlockSize, j*cBlockSize, cBlockSize , cBlockSize);
            rect->setBrush(QBrush(cGrassColor, Qt::SolidPattern));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
        }
    }
}