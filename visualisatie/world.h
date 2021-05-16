#ifndef TO_GROEP_WORLD_H
#define TO_GROEP_WORLD_H

#include <QGraphicsScene>
#include "../datastructures/Environment.h"
#include "../algorithms/MCLearning.h"

class QAction;
class QActionGroup;

class World : public QGraphicsScene
{
Q_OBJECT
public:
    explicit World(QObject* parent = 0);
    void drawTile(int x, int y, char type);
    void drawWorld();
    void refreshWorld();
    void setEnv(Environment newEnv);
    void togglePolicy(){fShowPolicy = !fShowPolicy;}
    void toggleTraining(){fTraining = !fTraining;}
    void updateAgent(LA* savedLA);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
signals:
    void clicked(int x,int y);
private:
    QColor cWaterColor;
    QColor cGrassColor;
    QColor cRockColor;

    bool fTraining = false;
    bool fShowPolicy = false;
    quint32 cBlockSize;
    qint32 focusRow, focusCol;
public:
    Environment env = Environment(10, 10, 42, true, -0.01, 10, 0.2);
    MCLearning agent = MCLearning(env, 0.01);

};

#endif //TO_GROEP_WORLD_H
