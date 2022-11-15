#ifndef FIREBALL_H
#define FIREBALL_H

#include <QObject>

class FireBall : public QObject
{
    Q_OBJECT
public:
    explicit FireBall(QObject *parent = nullptr);

signals:

};

#endif // FIREBALL_H
