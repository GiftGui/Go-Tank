#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>

class QKeyEvent;
class Tank;

class MyScene : public QGraphicsScene
{
public:
    explicit MyScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    Tank* player();
    void setPlayer(Tank* tank);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Tank* m_tank;
};

#endif // MYSCENE_H
