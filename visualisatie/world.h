#ifndef TO_GROEP_WORLD_H
#define TO_GROEP_WORLD_H

#include <QGraphicsScene>
#include "../datastructures/Environment.h"
#include "../algorithms/QLearning.h"
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
    void updateAgent(LA* savedLA);
    void drawPierePath();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
signals:
    void clicked(int x,int y);
private:
    bool fShowPolicy = false;
    quint32 cBlockSize;
    qint32 focusRow, focusCol;
public:
    Environment env = Environment(20, 20, 42, true, -0.01, 100, 0.2);
//    MCLearning agent = MCLearning(env, 0.1);
    QLearning agent = QLearning(&env, 0.1, 1, 0.9);

};

#endif //TO_GROEP_WORLD_H
