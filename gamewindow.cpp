#include "gamewindow.h"
#include "levelselectwindow.h"
#include "ui_gamewindow.h"
#include "gamemodel.h"
#include "gamecanvas.h"
#include "machineeditor.h"
#include <QMovie>
#include <QHBoxLayout>
#include <QPainter>
#include <QColor>
#include <QMessageBox>

GameWindow::GameWindow(GameModel& model, LevelSelectWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    // set robot gif
//    QMovie *robotmovie = new QMovie(":/elements/robot-idle-right.gif");
//    robotmovie->setScaledSize(QSize(robotSize, robotSize));
//    ui->robotLabel->setMovie(robotmovie);
//    robotmovie->start();

    // change the map when the user select new map
    connect(parent, &LevelSelectWindow::selectLevel, this, &GameWindow::changeLevel);
    connect(parent, &LevelSelectWindow::selectMap, this, &GameWindow::changeMap);

    // do not show the robot
    ui->robotLabel->setVisible(false);

    // Just for test, remove in final version
    connect(ui->startButton, &QPushButton::clicked, this, &GameWindow::gameStartTest);
    connect(ui->runningButton, &QPushButton::clicked, this, &GameWindow::runningTest);

    editor= new MachineEditor();


    // Get the game play area coordinate, for robot display
    gameAreaX = ui->gameArea->x();
    gameAreaY = ui->gameArea->y();

    // Connect the view to the model
    connect(&model, &GameModel::showEducationalMessage, this, &GameWindow::showEducationalMessage);
    connect(&model, &GameModel::mapLoaded, this, &GameWindow::changeMap);

    connect(this, &GameWindow::viewReady, &model, &GameModel::loadLevel);

    // When user creates a program
    // connect(editor, &MachineEditor::hereIsProgram, this, &GameWindow::runTheProgram);

    connect(ui->programButton, &QPushButton::clicked, this, &GameWindow::showProgram);


    emit viewReady();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::changeLevel(int levelNumber)
{
    // show the level number and welcome to the user
    QString num = QString::number(levelNumber);
    QString welcome = "Welcome to";
    QString levelNum = "Level " + num + "!";
    QFont font1("woshishabi", 32, QFont::Bold);
    QFont font2("woshishabi", 48, QFont::Bold);
    ui->welcomeLabel->setText(welcome);
    ui->welcomeLabel->setFont(font1);
    ui->levelLabel->setText(levelNum);
    ui->levelLabel->setFont(font2);
}

void GameWindow::showIdleRobot(QPoint position, int size)
{
    QMovie* rightWaiting = new QMovie(":/elements/robot-idle-right.gif");
    rightWaiting->setScaledSize(QSize(size, size));
    ui->robotLabel->setMovie(rightWaiting);
    rightWaiting->start();

    int x = position.x() + gameAreaX;
    int y = position.y() + gameAreaY;

    ui->robotLabel->setGeometry(x,y,size,size);
    ui->robotLabel->setVisible(true);
}

void GameWindow::showCheese(QPixmap cheese, QPoint position, int size)
{
    int cheeseX = position.x() + gameAreaX;
    int cheeseY = position.y() + gameAreaY;

    ui->cheese_label->setPixmap(cheese);

    ui->cheese_label->setGeometry(cheeseX,cheeseY,size,size);
    ui->cheese_label->setVisible(true);
}


void GameWindow::showRobotMovie(QMovie* theMovie){
    QMovie* rightWaiting = new QMovie(":/elements/robot-idle-right.gif");
    rightWaiting->setScaledSize(QSize(90, 90));
    ui->robotLabel->setMovie(rightWaiting);
    theMovie->start();
}

void GameWindow::changeMap(std::vector<std::vector<MapTile>> map)
{
    // show the map on canvas
    auto canvas = new GameCanvas(ui->scrollAreaWidgetContents, map);

    // get the robot and cheese position from the canvas, and set them on the window
    connect(canvas, &GameCanvas::robotMovie, this, &GameWindow::showRobotMovie);
    connect(canvas, &GameCanvas::showRobot, this, &GameWindow::showIdleRobot);
    connect(canvas, &GameCanvas::showCheese, this, &GameWindow::showCheese);
}

void GameWindow::gameStartTest()
{

}

void GameWindow::runningTest()
{

}

void GameWindow::showEducationalMessage(QString message) {
    qDebug() << "Message: " << message;
    QMessageBox::information(this, "About This Level", message);
}

void GameWindow::runTheProgram(std::vector<ProgramBlock> currentProgram) {
    // simu = Simulation(currentMap, currentProgram);
//    QTimer* runningTimer = new QTimer();
//    runningTimer->setInterval(25);
//    connect(runningTimer, &QTimer::timeout, this, &GameWindow::refreshRobot);
}

void GameWindow::showProgram() {
    editor->show();
}
