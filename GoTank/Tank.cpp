#include "Tank.h"
#include "MyScene.h"
#include "Bullet.h"
#include "MMO_Common.h"

#include <QPainter>

Tank::Tank() :
    m_direction(Direction::MoveUp),
    m_speed(TANK_SPEED)
{
    setPos(200,90);
}

QRectF Tank::boundingRect() const
{
    return QRectF(-UNIT_SIZE / 2, -UNIT_SIZE / 2,
                  UNIT_SIZE, UNIT_SIZE );
}

void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(this->shape(), Qt::red);
    QList<QGraphicsItem *> list = this->childItems();
    for(QGraphicsItem * item : list){
        painter->fillPath(item->shape(), Qt::red);
    }
    painter->restore();
}

Direction Tank::getDirection() const
{
    return m_direction;
}

void Tank::setDirection(Direction direction)
{
    m_direction = direction;
    if(m_direction == MoveDown){
        this->setRotation(180);
    }else if(m_direction == MoveLeft){
        this->setRotation(-90);
    }else if(m_direction == MoveRight){
        this->setRotation(90);
    }else{
        this->setRotation(0);
    }
}

void Tank::moveLeft()
{
    setDirection(MoveLeft);
    qreal x = pos().x();
    x -= m_speed;
    setPos(x, pos().y());
    while(checkColliding()){
        setPos(++x, pos().y());
    }
}

void Tank::moveRight()
{
    setDirection(MoveRight);
    qreal x = pos().x();
    x += m_speed;
    setPos(x, pos().y());
    while(checkColliding()){
        setPos(--x, pos().y());
    }
}

void Tank::moveUp()
{
    setDirection(MoveUp);
    qreal y = pos().y();
    y -= m_speed;
    setPos(pos().x(), y);
    while(checkColliding()){
        setPos(pos().x(), ++y);
    }
}

void Tank::moveDown()
{
    setDirection(MoveDown);
    qreal y = pos().y();
    y += m_speed;
    setPos(pos().x(), y);
    while(checkColliding()){
        setPos(pos().x(), --y);
    }
}

void Tank::explode()
{
    MyScene* s = dynamic_cast<MyScene*>(scene());
    s->removeItem(this);
//    delete this;
}

void Tank::shoot()
{
    MyScene* s = dynamic_cast<MyScene*>(scene());
    Bullet* b = new Bullet(m_direction);
    if(s == nullptr){
        return;
    }
    s->addItem(b);
    qreal x = pos().x();
    qreal y = pos().y();

    switch (m_direction) {
        case MoveLeft:
            b->setPos(x - 5 * UNIT_SIZE / 8, y);
            break;
        case MoveRight:
            b->setPos(x + 5 * UNIT_SIZE / 8, y);
            break;
        case MoveUp:
            b->setPos(x, y - 5 * UNIT_SIZE / 8);
            break;
        case MoveDown:
            b->setPos(x, y + 5 * UNIT_SIZE / 8);
            break;
    }
    sBulletDescription sb;
    sb.x = int32_t(b->pos().x());
    sb.y = int32_t(b->pos().y());
    sb.direction = m_direction;
    sb.vVel = uint32_t(BULLET_SPEED);
    emit signalShot(sb);
}

bool Tank::checkColliding()
{
    QList<QGraphicsItem*> list = collidingItems(Qt::IntersectsItemBoundingRect);
    return list.size() > 0;
}

QPainterPath Tank::shape() const
{
    QPainterPath p;
    p.addRect(QRectF(-UNIT_SIZE / 4, -UNIT_SIZE / 4, UNIT_SIZE / 2, UNIT_SIZE / 2));
    p.addRect(QRectF(-2, - UNIT_SIZE / 2, 4, UNIT_SIZE / 2));
    p.addRect(QRectF(- UNIT_SIZE / 2, - UNIT_SIZE / 2, UNIT_SIZE / 4, UNIT_SIZE));
    p.addRect(QRectF(UNIT_SIZE / 4, - UNIT_SIZE / 2, UNIT_SIZE / 4, UNIT_SIZE));
    return p;
}


