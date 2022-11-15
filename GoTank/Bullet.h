#ifndef BULLET_H
#define BULLET_H

#include <QObject>

#include <QGraphicsEllipseItem>
#include <QTimer>

#include "MMO_Common.h"

const int BULLET_SIZE = 6;
const int BULLET_SPEED = 8;

class Bullet : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit Bullet(Direction d, qreal x = - BULLET_SIZE / 2, qreal y = - BULLET_SIZE / 2,
                    qreal w = BULLET_SIZE / 2, qreal h = BULLET_SIZE / 2, QObject *parent = nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    Direction getDirection() const;
    void setDirection(Direction direction);

public slots:
    void getDown();

private:
    bool checkColliding();

protected:
    void advance(int step);

private:
    Direction b_direction;
    int b_speed;

    QTimer* timer;

signals:

};

#endif // BULLET_H
