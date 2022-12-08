#include "gamewindow.h"
#include "levelselectwindow.h"
#include "ui_gamewindow.h"
#include "gamecanvas.h"
#include "machinegraph.h"
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

    editor= new MachineEditor();

    // Get the game play area coordinate, for robot display
    gameAreaX = ui->gameArea->x();
    gameAreaY = ui->gameArea->y();

//    // Connect the view to the model
//    connect(&model, &GameModel::showEducationalMessage, this, &GameWindow::showEducationalMessage);
//    connect(&model, &GameModel::mapLoaded, this, &GameWindow::changeMap);

//    connect(this, &GameWindow::viewReady, &model, &GameModel::loadLevel);


    // Connects program pannel.
    MachineGraph *graph = new MachineGraph();
    ui->mainLayout->insertWidget(0, graph);
    connect(ui->connectButton, &QPushButton::clicked, graph,
            &MachineGraph::toggleConnecting);
    connect(ui->resetBegin, &QPushButton::clicked, graph,
            &MachineGraph::resetBegin);

    connect(graph, &MachineGraph::connectToggled, this,
            &GameWindow::connectToggled);

    connect(ui->ifButton, &QPushButton::clicked, this,
            &GameWindow::ifButtonPushed);
    connect(ui->facingWallButton, &QPushButton::clicked, this,
            &GameWindow::facingWallButtonPushed);
    connect(ui->notButton, &QPushButton::clicked, this,
            &GameWindow::notButtonPushed);
    connect(ui->moveForward, &QPushButton::clicked, this,
            &GameWindow::moveForwardButtonPushed);
    connect(ui->turnLeftButton, &QPushButton::clicked, this,
            &GameWindow::turnLeftButtonPushed);
    connect(ui->turnRightButton, &QPushButton::clicked, this,
            &GameWindow::turnRightButtonPushed);
    connect(ui->facingPitButton, &QPushButton::clicked, this,
            &GameWindow::facingPitButtonPushed);
    connect(ui->eatCheeseButton, &QPushButton::clicked, this,
            &GameWindow::eatCheeseButtonPushed);
    connect(ui->endWhileButton, &QPushButton::clicked, this,
            &GameWindow::endWhileButtonPushed);
    connect(ui->endIfButton, &QPushButton::clicked, this,
            &GameWindow::endIfButtonPushed);
    connect(ui->whileButton, &QPushButton::clicked, this,
            &GameWindow::whilePushed);
    connect(ui->facingBlock, &QPushButton::clicked, this,
            &GameWindow::facingBlockButtonPushed);
    connect(ui->facingCheese, &QPushButton::clicked, this,
            &GameWindow::facingCheeseButtonPushed);

    connect(ui->getOutput, &QPushButton::clicked, graph,
            &MachineGraph::getProgram);

    // Get program from the graph and send it to the game window
    connect(graph, &MachineGraph::programData,canvas, &GameCanvas::simulate);
    connect(this, &GameWindow::changeType, graph, &MachineGraph::setType);
    connect(canvas, &GameCanvas::currentBlock, graph, &MachineGraph::setRunningBlock);



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

void GameWindow::ifButtonPushed() {
  emit changeType(ProgramBlock::ifStatement);
}
void GameWindow::facingWallButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingWall);
}
void GameWindow::notButtonPushed() {
  emit changeType(ProgramBlock::conditionNot);
}
void GameWindow::moveForwardButtonPushed() {
  emit changeType(ProgramBlock::moveForward);
}
void GameWindow::turnLeftButtonPushed() {
  emit changeType(ProgramBlock::turnLeft);
}
void GameWindow::turnRightButtonPushed() {
  emit changeType(ProgramBlock::turnRight);
}
void GameWindow::facingPitButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingPit);
}
void GameWindow::eatCheeseButtonPushed() {
  emit changeType(ProgramBlock::eatCheese);
}
void GameWindow::endWhileButtonPushed() {
  emit changeType(ProgramBlock::endWhile);
}
void GameWindow::endIfButtonPushed() {
  emit changeType(ProgramBlock::endIf);
}
void GameWindow::whilePushed() { emit changeType(ProgramBlock::whileLoop); }
void GameWindow::facingBlockButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingBlock);
}
void GameWindow::facingCheeseButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingCheese);
}

void GameWindow::connectToggled(bool connecting) {
  if (connecting) {
    ui->connectButton->setStyleSheet("background-color: rgb(255, 0, 0);font: "
                                     "700 9pt \"Microsoft YaHei UI\";");
    ui->connectButton->setText("Cancel");
  } else {
    ui->connectButton->setStyleSheet("font: 700 9pt \"Microsoft YaHei UI\";");
    ui->connectButton->setText("Connect Blocks");
  }
}

