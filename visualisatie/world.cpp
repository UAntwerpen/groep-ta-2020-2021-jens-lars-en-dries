#include "world.h"

#include <QtWidgets>
#include <QPixmap>

World::World(QObject* parent ): QGraphicsScene(parent){
    cBlockSize = 40;
}

void World::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    QPointF scenePos = mouseEvent->scenePos();

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
            rect->setBrush(QBrush(QPixmap("visualisatie/graphics/grass.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'O':
            rect->setBrush(QBrush(QPixmap("visualisatie/graphics/rock.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            break;
        case 'E':
            rect->setBrush(QBrush(QPixmap("visualisatie/graphics/house.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            break;
        case 'S':
            rect->setBrush(QBrush(QPixmap("visualisatie/graphics/pierre.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'b':
            rect->setBrush(QBrush(QPixmap("visualisatie/graphics/bridge.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'w':
            rect->setBrush(QBrush(QPixmap("visualisatie/graphics/water.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
            rect->setCacheMode(QGraphicsItem::NoCache);
            addItem(rect);
            if(fShowPolicy){
                int action = agent.getLA().argmax(agent.getLA().coordinatesToState(tuple(x, y)));
                switch (action) {
                    case 0:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aUp.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 1:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aRight.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 2:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aDown.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                    case 3:
                        policy->setBrush(QBrush(QPixmap("visualisatie/graphics/aLeft.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
                        policy->setCacheMode(QGraphicsItem::NoCache);
                        addItem(policy);
                        break;
                }
            }
            break;
        case 'L':
            rect->setBrush(QBrush(QPixmap("visualisatie/graphics/lava.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
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
//    agent = MCLearning(env, 0.01);
    agent.load(savedLA);
}

void World::drawPierePath() {

    LA deterministic_automaton = agent.getLA().toDeterministic();
    std::pair<int,int> current_coordinates = std::make_pair(env.start->x, env.start->y);
    unsigned int step_count = 0;
    env.reset();

    while(current_coordinates != std::make_pair(env.end->x, env.end->y) and step_count<300) {

        State* next_state = deterministic_automaton.coordinatesToState(current_coordinates);
        current_coordinates = deterministic_automaton.G(next_state,deterministic_automaton.pickAction(next_state))->getCoordinates();

        QGraphicsRectItem *pierre = new QGraphicsRectItem( current_coordinates.first*cBlockSize, (env.height - current_coordinates.second)*cBlockSize, cBlockSize , cBlockSize);
        pierre->setBrush(QBrush(QPixmap("visualisatie/graphics/pierre001.png").scaled(cBlockSize,cBlockSize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
        pierre->setCacheMode(QGraphicsItem::NoCache);
        addItem(pierre);

        step_count++;
    }
}
