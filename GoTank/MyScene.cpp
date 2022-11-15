#include "MyScene.h"

#include <QKeyEvent>
#include <QDebug>

#include "Tank.h"

MyScene::MyScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene{x, y, width, height, parent},
      m_tank(new Tank())
{
    this->addItem(m_tank);
}

Tank *MyScene::player()
{
    return m_tank;
}

void MyScene::setPlayer(Tank *tank)
{
    m_tank = tank;
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            m_tank->moveLeft();
            break;
        case Qt::Key_Right:
            m_tank->moveRight();
            break;
        case Qt::Key_Up:
            m_tank->moveUp();
            break;
        case Qt::Key_Down:
            m_tank->moveDown();
            break;
        case Qt::Key_Space:
            m_tank->shoot();
    }
}
