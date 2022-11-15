#ifndef BRICKWALL_H
#define BRICKWALL_H

#include <QGraphicsRectItem>

#include "MMO_Common.h"

class BrickWall : public QGraphicsRectItem
{
public:
    BrickWall(qreal x,qreal y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;

    void explode();
};

#endif // BRICKWALL_H
