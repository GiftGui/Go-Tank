#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <unordered_map>
#include "MMO_Common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QGraphicsScene;
class QGraphicsView;
class QKeyEvent;
class Tank;
class MyScene;
class GameDialog;

const int INTERVAL = 30;

class MainWindow : public QMainWindow, olc::net::client_interface<GameMsg>
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onUserUpdate();

private slots:
    void adjustViewSize();
    void onUserShoot(sBulletDescription sb);
    void continueGame();

private:
    void initScene();
    void updateDesc();
    void updateTank(sPlayerDescription desc, Tank* tank);
    bool checkAlive();
    void reset();

private:
    Ui::MainWindow *ui;

    MyScene *scene;
    QGraphicsView *view;

    QTimer timer;
    std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
    std::unordered_map<uint32_t, Tank*> mapTanks;
    uint32_t nPlayerID = 0;

    sPlayerDescription descPlayer;
    bool bWaitingForConnection = true;
    Tank* m_player = nullptr;

    GameDialog* gDialog = nullptr;

    int vWorldSize = 32;

    std::string sWorldMap =
            "################################"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..........####...####.........#"
            "#..........#.........#.........#"
            "#..........#.........#.........#"
            "#..........#.........#.........#"
            "#..........##############......#"
            "#..............................#"
            "#..................#.#.#.#.....#"
            "#..............................#"
            "#..................#.#.#.#.....#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "#..............................#"
            "################################";
};
#endif // MAINWINDOW_H
