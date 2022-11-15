#include "BrickWall.h"

#include <QPainter>

BrickWall::BrickWall(qreal x,qreal y)
{
    setPos(x, y);
}

QRectF BrickWall::boundingRect() const
{
    return QRectF(-UNIT_SIZE / 2, -UNIT_SIZE / 2,
                  UNIT_SIZE, UNIT_SIZE );
}

void BrickWall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(this->shape(), Qt::black);
    painter->restore();
}

QPainterPath BrickWall::shape() const
{
    QPainterPath p;
    p.addRect(QRectF(-UNIT_SIZE / 2, -UNIT_SIZE / 2, UNIT_SIZE, UNIT_SIZE));
    return p;
}
