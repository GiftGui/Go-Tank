#include "Bullet.h"
#include "Tank.h"
#include <QPainter>
#include "MyScene.h"
#include "BrickWall.h"

Bullet::Bullet(Direction d, qreal x, qreal y, qreal w, qreal h, QObject* parent) :
    QObject(parent),
    QGraphicsEllipseItem(x, y, w, h),
    b_direction(d),
    b_speed(BULLET_SPEED)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &Bullet::getDown);
    timer->start(3000);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-BULLET_SIZE / 2, -BULLET_SIZE / 2,
                  BULLET_SIZE, BULLET_SIZE );
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(this->shape(), Qt::white);
    painter->restore();
}

Direction Bullet::getDirection() const
{
    return b_direction;
}

void Bullet::setDirection(Direction direction)
{
    b_direction = direction;
}

void Bullet::getDown()
{
    MyScene* s = dynamic_cast<MyScene*>(scene());
    s->removeItem(this);
    delete this;
}

bool Bullet::checkColliding()
{
    for(QGraphicsItem* item: collidingItems(Qt::IntersectsItemBoundingRect)) {
        if (Tank *t = qgraphicsitem_cast<Tank*>(item)) {
            t->explode();
            return true;
        }else if(BrickWall* bw = qgraphicsitem_cast<BrickWall*>(item)){
            return true;
        }
    }
    return false;
}

void Bullet::advance(int step)
{
    if (!step) {
        return;
    }
    qreal x = pos().x();
    qreal y = pos().y();
    qreal speed = qreal(b_speed);

    switch (b_direction) {
        case MoveLeft:
            x -= speed;
            break;
        case MoveRight:
            x += speed;
            break;
        case MoveUp:
            y -= speed;
            break;
        case MoveDown:
            y += speed;
            break;
    }

    setPos(x, y);
    if(checkColliding()){
        getDown();
    }
}
