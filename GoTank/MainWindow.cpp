#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

#include "Tank.h"
#include "MyScene.h"
#include "Bullet.h"
#include "MMO_Common.h"
#include "GameDialog.h"
#include "BrickWall.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if (Connect("127.0.0.1", 60000))
    {
        qDebug() << "Connecting.../n";
    }
    initScene();
    timer.setInterval(INTERVAL);

    connect(&timer, &QTimer::timeout, this, &MainWindow::onUserUpdate);
    timer.start();
    connect(scene->player(), &Tank::signalShot, this, &MainWindow::onUserShoot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUserUpdate()
{
    // Check for incoming network messages
    if (IsConnected())
    {
        while (!Incoming().empty())
        {
            auto msg = Incoming().pop_front().msg;

            switch (msg.header.id)
            {
            case(GameMsg::Client_Accepted):
            {
                qDebug() << "Server accepted client - you're in!\n";
                olc::net::message<GameMsg> msg;
                msg.header.id = GameMsg::Client_RegisterWithServer;
                //?
                updateDesc();
                msg << descPlayer;
                Send(msg);
                break;
            }

            case(GameMsg::Client_AssignID):
            {
                // Server is assigning us OUR id
                msg >> nPlayerID;
                descPlayer.nUniqueID = nPlayerID;
                qDebug() << "Assigned Client ID = " << nPlayerID << "\n";
                break;
            }

            case(GameMsg::Game_AddPlayer):
            {
                sPlayerDescription desc;
                msg >> desc;
                uint32_t id = desc.nUniqueID;
                mapObjects.insert_or_assign(id, desc);
                if (desc.nUniqueID == nPlayerID)
                {
                    // Now we exist in game world
                    bWaitingForConnection = false;
                }else{
                    if(mapTanks.find(id)!=mapTanks.end()){
                        updateTank(desc, mapTanks[id]);
                    }else{
                        Tank* tank = new Tank();
                        updateTank(desc, tank);
                        scene->addItem(tank);
                        mapTanks[id] = tank;
                    }
                }
                break;
            }

            case(GameMsg::FireBullet):
            {
                sBulletDescription desc;
                msg >> desc;
                Bullet* bullet = new Bullet(desc.direction);
                bullet->setPos(desc.x, desc.y);
                scene->addItem(bullet);
                break;
            }

            case(GameMsg::Game_RemovePlayer):
            {
                uint32_t nRemovalID = 0;
                msg >> nRemovalID;
                mapObjects.erase(nRemovalID);
                Tank* rTank = mapTanks[nRemovalID];
                mapTanks.erase(nRemovalID);
/*
                if(rTank){
                    scene->removeItem(rTank);
                    delete rTank;
                }
*/
                break;
            }

            case(GameMsg::Game_UpdatePlayer):
            {
                sPlayerDescription desc;
                msg >> desc;
                uint32_t id = desc.nUniqueID;
                mapObjects.insert_or_assign(id, desc);
                if(id != nPlayerID){
                    if(mapTanks.find(id)==mapTanks.end()){
                        Tank* aTank = new Tank();
                        updateTank(desc, aTank);
                        mapTanks[id] = aTank;
                        scene->addItem(aTank);
                    }else{
                        Tank* tank = mapTanks[id];
                        updateTank(desc, tank);
                    }
                }
                break;
            }

            }
        }
    }

    if (bWaitingForConnection)
    {
//      Clear(olc::DARK_BLUE);
//      DrawString({ 10,10 }, "Waiting To Connect...", olc::WHITE);
//      return true;
        return;
    }

    if(!checkAlive()){
        olc::net::message<GameMsg> msgRemoveMyself;
        msgRemoveMyself.header.id = GameMsg::Game_RemovePlayer;
        msgRemoveMyself << nPlayerID;
        Send(msgRemoveMyself);
        reset();
//        QMessageBox::information(this, tr("Info"), "Game Over");
    }else{
        // Send player description
        olc::net::message<GameMsg> msg;
        msg.header.id = GameMsg::Game_UpdatePlayer;
        updateDesc();
        msg << descPlayer;
        Send(msg);
        scene->advance();
    }
}

void MainWindow::initScene()
{
//    gDialog->hide();
    resize(1180,1180);
    scene = new MyScene(-22.5, -22.5, 1080, 1080);
    scene->setBackgroundBrush(Qt::gray);

    for(int x = 0;x < vWorldSize; ++x){
        for(int y = 0; y < vWorldSize; ++y){
            if(sWorldMap[x * vWorldSize + y] == '#'){
                BrickWall* bw = new BrickWall(x * UNIT_SIZE, y * UNIT_SIZE);
                scene->addItem(bw);
            }
        }
    }
//  BrickWall* bw = new BrickWall(10,10);
//  scene->addItem(bw);

    view = new QGraphicsView;
    view->setScene(scene);
    setCentralWidget(view);

    m_player = scene->player();
}

void MainWindow::updateDesc()
{
    descPlayer.x = scene->player()->pos().x();
    descPlayer.y = scene->player()->pos().y();
    descPlayer.direction = scene->player()->getDirection();
//  descPlayer.nUniqueID = nPlayerID;
}

void MainWindow::updateTank(sPlayerDescription desc, Tank *tank)
{
    tank->setPos(desc.x, desc.y);
    tank->setDirection(desc.direction);
}

bool MainWindow::checkAlive()
{
    if(m_player->scene()!=nullptr) return true;
    return false;
}

void MainWindow::reset()
{
    if(gDialog == nullptr){
        gDialog = new GameDialog(this);
//        connect(gDialog->continueButton, &QPushButton::clicked, this, &MainWindow::continueGame);
        connect(gDialog->quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    }
    gDialog->exec();
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::onUserShoot(sBulletDescription sb)
{
    if (bWaitingForConnection)
    {
        return;
    }
    // Send bullet description
    olc::net::message<GameMsg> msg;
    msg.header.id = GameMsg::FireBullet;
    msg << sb;
    Send(msg);
}

void MainWindow::continueGame()
{
    //restart Scene
    Tank* tank = scene->player();
    tank = new Tank();
    m_player = tank;
    scene->addItem(tank);
    scene->setPlayer(tank);
}

