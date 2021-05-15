#include "world.h"

#include <QtWidgets>
#include <QPixmap>

World::World(QObject* parent ): QGraphicsScene(parent){
    cGrassColor = Qt::green;
    cRockColor = Qt::gray;
    cWaterColor = Qt::blue;
    cBlockSize = 30;
}

void World::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    QPointF scenePos = mouseEvent->scenePos();
//    if( scenePos.x() < 0 || scenePos.y() < 0 || scenePos.x() > 8 || scenePos.y() > 8 )
//    {
//        focusRow = -1;
//        focusCol = -1;
//        return;
//    }

    focusRow = int(scenePos.y()) / cBlockSize;
    focusCol = int(scenePos.x()) / cBlockSize;

    emit(clicked((int) focusRow, (int) focusCol));


    QGraphicsScene::mousePressEvent(mouseEvent);
}

void World::drawTile(int x, int y, char type){
    QGraphicsRectItem *rect = new QGraphicsRectItem( x*cBlockSize, y*cBlockSize, cBlockSize , cBlockSize);
    switch (type) {
        case '.':
            rect->setBrush(QBrush(cGrassColor, Qt::SolidPattern));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            break;
        case 'O':
            rect->setBrush(QBrush(cRockColor, Qt::SolidPattern));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            break;
    }
}

void World::drawWorld() {
    for (int x = 0; x < env.height; x++) {
        for (int y = 0; y < env.width; y++) {
            MDPState *state = env.get_state_by_coordinates(x, y);
            drawTile(state->x, state->y, state->symbol[0]);
        }
    }

}

void World::setEnv(Environment newEnv) {
    env = newEnv;
}
