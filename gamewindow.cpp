#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gamemodel.h"
#include "gamecanvas.h"
#include <QMovie>
#include <QHBoxLayout>
#include <QPainter>
#include <QColor>
#include <QMessageBox>

GameWindow::GameWindow(GameModel& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    robotSize = 90;

    QMovie *robotmovie = new QMovie(":/elements/robot-idle-right.gif");
    robotmovie->setScaledSize(QSize(robotSize, robotSize));
    ui->robotLabel->setMovie(robotmovie);
    robotmovie->start();

    ui->robotLabel->setVisible(false);


    // Just for test, remove in final version
    connect(ui->startButton, &QPushButton::clicked, this, &GameWindow::gameStartTest);
    connect(ui->runningButton, &QPushButton::clicked, this, &GameWindow::runningTest);


    // Get the game play area coordinate, for robot display
    gameAreaX = ui->gameArea->x();
    gameAreaY = ui->gameArea->y();

    // Connect the view to the model
    connect(&model, &GameModel::showEducationalMessage, this, &GameWindow::showEducationalMessage);
    connect(&model, &GameModel::mapLoaded, this, &GameWindow::changeMap);
    connect(this, &GameWindow::viewReady, &model, &GameModel::loadLevel);

    emit viewReady();
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

    QString x = QString::number(position.x());
    ui->debugLabel->setText("x is " + x);

    ui->robotLabel->setGeometry(robotX,robotY,robotSize,robotSize);
    ui->robotLabel->setVisible(true);
}

void GameWindow::showCheese(QPoint position)
{
    int cheeseX = position.x() + gameAreaX;
    int cheeseY = position.y() + gameAreaY;

    QPixmap cheeseMap(":/elements/cheese.png");
    QPixmap scaledCheeseMap = cheeseMap.scaled(robotSize, robotSize, Qt::KeepAspectRatio);

    ui->cheese_label->setPixmap(scaledCheeseMap);

    ui->cheese_label->setGeometry(cheeseX,cheeseY,robotSize,robotSize);
    ui->cheese_label->setVisible(true);
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
    connect(canvas, &GameCanvas::showRobot, this, &GameWindow::showIdleRobot);
    connect(canvas, &GameCanvas::showCheese, this, &GameWindow::showCheese);
}

void GameWindow::gameStartTest()
{
    QPoint robotPosition = QPoint(0, 0);

    showIdleRobot(robotPosition);
}

void GameWindow::runningTest()
{

}

void GameWindow::showEducationalMessage(QString message) {
    qDebug() << "Message: " << message;
    QMessageBox::information(this, "About This Level", message);
}
