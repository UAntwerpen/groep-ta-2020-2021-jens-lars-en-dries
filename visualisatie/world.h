#ifndef TO_GROEP_WORLD_H
#define TO_GROEP_WORLD_H

#include <QGraphicsScene>

class QAction;
class QActionGroup;

class World : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit World(QObject* parent = 0);
    void drawTile();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    signals:
            void clicked(int x,int y);
private:
    QColor cWaterColor;
    QColor cGrassColor;


    quint32 cBlockSize;
    qint8 focusRow, focusCol;


};

#endif //TO_GROEP_WORLD_H
