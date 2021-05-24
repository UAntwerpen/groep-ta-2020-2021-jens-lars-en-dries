#include "world.h"

#include <QtWidgets>
#include <QPixmap>

// TODO : Fix ghost policy door argmax funcie.

World::World(QObject* parent ): QGraphicsScene(parent){
    cGrassColor = Qt::green;
    cRockColor = Qt::gray;
    cWaterColor = Qt::blue;
    cBlockSize = 40;
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
    QGraphicsRectItem *rect = new QGraphicsRectItem( (x)*cBlockSize, (env.height - y)*cBlockSize, cBlockSize , cBlockSize);

    QGraphicsRectItem *policy = new QGraphicsRectItem( x*cBlockSize, (env.height - y)*cBlockSize, cBlockSize , cBlockSize);

    switch (type) {
        case '.':
            rect->setBrush(QBrush(QPixmap("visualisatie/grass.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'O':
            rect->setBrush(QBrush(QPixmap("visualisatie/rock.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            break;
        case 'E':
            rect->setBrush(QBrush(QPixmap("visualisatie/house.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            break;
        case 'S':
            rect->setBrush(QBrush(QPixmap("visualisatie/pierre.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'b':
            rect->setBrush(QBrush(QPixmap("visualisatie/bridge.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'w':
            rect->setBrush(QBrush(QPixmap("visualisatie/water.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'L':
            rect->setBrush(QBrush(QPixmap("visualisatie/lava.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            break;
    }
    if(!fShowPolicy){
        delete policy;
    }
}

void World::drawWorld() {
    for (int x = 0; x < env.height; x++) {
        for (int y = 0; y < env.width; y++) {
            MDPState *state = env.get_state_by_coordinates(x, y);
            if(env.startcoords == tuple(x, y)){
                drawTile(state->x, state->y, 'S');
            }
            else{
                if(x == 19 && y == 19){
                    cout << "stop right there criminal scum";
                }
                drawTile(state->x, state->y, state->symbol[0]);
            }
        }
    }

}

void World::setEnv(Environment newEnv) {
    env = newEnv;
}

void World::refreshWorld() {
    qDeleteAll( items() );
    drawWorld();
}

void World::updateAgent(LA *savedLA) {
    agent = MCLearning(env, 0.01);
    agent.load(savedLA);
}
