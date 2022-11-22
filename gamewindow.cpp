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

    // Set a timer for running


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

    // Setup idle robot label
//    ui->robotLabel->setVisible(false);
//    QMovie *robotmovie = new QMovie(":/elements/robot-idle.gif");
//    robotmovie->setScaledSize(QSize(50, 50));
//    ui->robotLabel->setMovie(robotmovie);
//    robotmovie->start();

    // Setip running robot label
//    ui->runningRobotLabel->setVisible(false);
//    QMovie *runningRobotmovie = new QMovie(":/elements/robot-run.gif");
//    runningRobotmovie->setScaledSize(QSize(50, 50));
//    ui->robotLabel->setMovie(runningRobotmovie);
//    runningRobotmovie->start();

    connect(canvas, &GameCanvas::showRobot, this, &GameWindow::showIdleRobot);


}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::showIdleRobot(QPoint position)
{
    int x = position.x() + gameAreaX;
    int y = position.y() + gameAreaY;

    robotX = position.x() + gameAreaX;
    robotY = position.y() + gameAreaY;

    QMovie *robotmovie = new QMovie(":/elements/robot-idle.gif");
    robotmovie->setScaledSize(QSize(50, 50));
    ui->robotLabel->setMovie(robotmovie);
    robotmovie->start();

    ui->robotLabel->setGeometry(x,y,60,60);
    ui->robotLabel->setVisible(true);
}

void GameWindow::showMovingRobot(QPoint position)
{
    int x = position.x() + gameAreaX;
    int y = position.y() + gameAreaY;

    QMovie *runningRobotmovie = new QMovie(":/elements/robot-run.gif");
    runningRobotmovie->setScaledSize(QSize(50, 50));
    ui->robotLabel->setMovie(runningRobotmovie);
    runningRobotmovie->start();

    ui->robotLabel->setGeometry(x,y,60,60);
}

void GameWindow::showOneBrick(QPoint position)
{
//    int x = position.x();
//    int y = position.y();
//    QPixmap image(":/elements/brickwall.jpg");
//    image.scaled(QSize(50, 50));

//    QLabel *label = new QLabel();
//    label->setPixmap(image);
//    label->setGeometry(x,y,60,60);
//    ui->bricksLayout->addWidget(label,1,0);
//    label->show();
}

void GameWindow::gameStartTest()
{
    // QPoint robotPosition = QPoint(gameAreaX, gameAreaY);
    QPoint robotPosition = QPoint(0, 0);

    showIdleRobot(robotPosition);
}

void GameWindow::runningTest()
{
    QPoint robotPosition = QPoint(0, 0);

    robotTimer = new QTimer();
    connect(robotTimer, &QTimer::timeout, this, &GameWindow::move);
    robotTimer->start(30);

    showMovingRobot(robotPosition);
}

void GameWindow::move()
{
    robotX++;
    ui->robotLabel->setGeometry(robotX,robotY,60,60);
}

