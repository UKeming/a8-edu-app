#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gamemodel.h"

GameWindow::GameWindow(GameModel& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}
