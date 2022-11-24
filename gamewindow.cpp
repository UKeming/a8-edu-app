#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gamemodel.h"
#include "gamecanvas.h"
#include <QMovie>
#include <QHBoxLayout>
#include <QPainter>
#include <QColor>

GameWindow::GameWindow(GameModel& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    robotSize = 90;

    // Set a timer to check the postion of robot
//    robotTimer = new QTimer();
//    robotTimer->start(10);
//    connect(robotTimer, &QTimer::timeout, this, &GameWindow::refreshRobot);

    // Just for test, remove in final version
    connect(ui->startButton, &QPushButton::clicked, this, &GameWindow::gameStartTest);
    connect(ui->runningButton, &QPushButton::clicked, this, &GameWindow::runningTest);

    // Get the game play area coordinate, for robot display
    gameAreaX = ui->gameArea->x();
    gameAreaY = ui->gameArea->y();

    // Canvas setup
    std::vector<std::vector<MapTile>> tempMap = std::vector<std::vector<MapTile>>{
                                                                                 std::vector<MapTile>{ground, ground, ground,  ground,  ground,  wall },
                                                                                 std::vector<MapTile>{wall,  wall,  wall, wall,  ground ,  wall },
                                                                                 std::vector<MapTile>{wall,  wall,  wall, wall,  ground ,  wall },
                                                                                 std::vector<MapTile>{wall,  wall,  wall, wall,  cheese ,  wall }
                                                                             };
    // Show the temp map
    auto canvas = new GameCanvas(ui->scrollAreaWidgetContents, tempMap);

    connect(canvas, &GameCanvas::showRobot, this, &GameWindow::showIdleRobot);


}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::refreshRobot()
{
    // QPoint* destination = ...getRobotPos();
    QPoint destination = QPoint(0, 0);
    if(destination.x() != robotX || destination.y() != robotY)
    {
        robotX = destination.x();
        robotY = destination.y();
        if(destination.x() >= robotX && !facingRight)
        {
            facingRightRunning();
            facingRight = true;
        }
        if(destination.x() < robotX && facingRight)
        {
            facingLeftRunning();
            facingRight = false;
        }
        ui->robotLabel->setGeometry(robotX,robotY,robotSize,robotSize);
    }
    showIdleRobot(destination);
}

void GameWindow::showIdleRobot(QPoint position)
{
    robotX = position.x() + gameAreaX;
    robotY = position.y() + gameAreaY;

    QMovie *robotmovie = new QMovie(":/elements/robot-idle.gif");
    robotmovie->setScaledSize(QSize(robotSize, robotSize));
    ui->robotLabel->setMovie(robotmovie);
    robotmovie->start();

    ui->robotLabel->setGeometry(robotX,robotY,robotSize,robotSize);
    ui->robotLabel->setVisible(true);
}

void GameWindow::facingRightWaiting()
{
    QMovie *robotmovie = new QMovie(":/elements/robot-idle-right.gif");
    robotmovie->setScaledSize(QSize(robotSize, robotSize));
    ui->robotLabel->setMovie(robotmovie);
    robotmovie->start();
}

void GameWindow::facingLeftWaiting()
{
    QMovie *robotmovie = new QMovie(":/elements/robot-idle-left.gif");
    robotmovie->setScaledSize(QSize(robotSize, robotSize));
    ui->robotLabel->setMovie(robotmovie);
    robotmovie->start();
}

void GameWindow::facingRightRunning()
{
    QMovie *runningRobotmovie = new QMovie(":/elements/robot-run-right.gif");
    runningRobotmovie->setScaledSize(QSize(robotSize, robotSize));
    ui->robotLabel->setMovie(runningRobotmovie);
    runningRobotmovie->start();
}

void GameWindow::facingLeftRunning()
{
    QMovie *runningRobotmovie = new QMovie(":/elements/robot-run-left.gif");
    runningRobotmovie->setScaledSize(QSize(robotSize, robotSize));
    ui->robotLabel->setMovie(runningRobotmovie);
    runningRobotmovie->start();
}

void GameWindow::changeMap(std::vector<std::vector<MapTile>> map)
{
    auto canvas = new GameCanvas(ui->scrollAreaWidgetContents, map);
}

void GameWindow::gameStartTest()
{
    // QPoint robotPosition = QPoint(gameAreaX, gameAreaY);
    QPoint robotPosition = QPoint(0, 0);

    showIdleRobot(robotPosition);
}

void GameWindow::runningTest()
{

}