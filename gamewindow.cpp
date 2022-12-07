#include "gamewindow.h"
#include "levelselectwindow.h"
#include "ui_gamewindow.h"
#include "gamecanvas.h"
#include "machineeditor.h"
#include <QMovie>
#include <QHBoxLayout>
#include <QPainter>
#include <QColor>
#include <QMessageBox>

GameWindow::GameWindow(std::vector<std::vector<MapTile>> map, int levelNumber, LevelSelectWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    // show the map on canvas
    canvas = new GameCanvas(ui->scrollAreaWidgetContents, map);
    // get the robot and cheese position from the canvas, and set them on the window
    connect(canvas, &GameCanvas::robotMovie, this, &GameWindow::showRobotMovie);
    connect(canvas, &GameCanvas::showRobot, this, &GameWindow::showIdleRobot);
    connect(canvas, &GameCanvas::showCheese, this, &GameWindow::showCheese);
    connect(canvas, &GameCanvas::gameLost, this, &GameWindow::lost);
    connect(canvas, &GameCanvas::restartGame, this, &GameWindow::restart);
    connect(canvas, &GameCanvas::gameWon, this, &GameWindow::gameWon);
    // show the level number and welcome to the user
    QString num = QString::number(levelNumber + 1);
    QString welcome = "Welcome to";
    QString levelNum = "Level " + num + "!";
    QFont font1("woshishabi", 32, QFont::Bold);
    QFont font2("woshishabi", 48, QFont::Bold);
    ui->welcomeLabel->setText(welcome);
    ui->welcomeLabel->setFont(font1);
    ui->levelLabel->setText(levelNum);
    ui->levelLabel->setFont(font2);

    // change the map when the user select new map
//    connect(parent, &LevelSelectWindow::selectLevel, this, &GameWindow::changeLevel);
//    connect(parent, &LevelSelectWindow::selectMap, this, &GameWindow::changeMap);

    // do not show the robot
    ui->robotLabel->setVisible(false);

    // Just for test, remove in final version
    connect(ui->startButton, &QPushButton::clicked, this, &GameWindow::gameStartTest);
    connect(ui->runningButton, &QPushButton::clicked, this, &GameWindow::runningTest);

    editor= new MachineEditor();

    // Get the game play area coordinate, for robot display
    gameAreaX = ui->gameArea->x();
    gameAreaY = ui->gameArea->y();

//    // Connect the view to the model
//    connect(&model, &GameModel::showEducationalMessage, this, &GameWindow::showEducationalMessage);
//    connect(&model, &GameModel::mapLoaded, this, &GameWindow::changeMap);

//    connect(this, &GameWindow::viewReady, &model, &GameModel::loadLevel);

    // When user creates a program
    connect(editor, &MachineEditor::programData, canvas, &GameCanvas::simulate);

    connect(ui->programButton, &QPushButton::clicked, this, &GameWindow::showProgram);


    emit viewReady();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::showIdleRobot(QPoint position, int size)
{
    int x = position.x() + gameAreaX;
    int y = position.y() + gameAreaY;

    ui->robotLabel->setGeometry(x,y,size,size);
    ui->robotLabel->setVisible(true);
}

void GameWindow::showCheese(QPoint position, int size)
{
    int cheeseX = position.x() + gameAreaX;
    int cheeseY = position.y() + gameAreaY;

    QPixmap cheeseMap(":/elements/cheese.png");
    QPixmap scaledCheeseMap = cheeseMap.scaled(size, size, Qt::KeepAspectRatio);

    ui->cheese_label->setPixmap(scaledCheeseMap);

    ui->cheese_label->setGeometry(cheeseX,cheeseY,size,size);
    ui->cheese_label->setVisible(true);
}


void GameWindow::showRobotMovie(QMovie* theMovie){
    ui->robotLabel->setMovie(theMovie);
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


void GameWindow::showProgram() {
    editor->show();
}

void GameWindow::lost(){
    QString lost = "You lost in";
    ui->welcomeLabel->setText(lost);
    QPoint respawn = QPoint(0,0);
    showIdleRobot(respawn, 90);
}

void GameWindow::restart(){
    QString restart = "Welcome to";
    ui->welcomeLabel->setText(restart);
}

void GameWindow::gameWon(){

}
