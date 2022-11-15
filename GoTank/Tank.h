#ifndef TANK_H
#define TANK_H

#include <deque>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include "MMO_Common.h"
#include <QObject>


const int TANK_SPEED = 5;

class Bullet;

class Tank : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Tank();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
    Direction getDirection() const;
    void setDirection(Direction direction);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void explode();
    void shoot();

private:
    bool checkColliding();

signals:
    void signalShot(sBulletDescription);

private:
    Direction m_direction;
    int m_speed;
//    bool
//    std::deque<Bullet*> clip;
};

#endif // TANK_H
