#include "levelselectwindow.h"
#include "ui_levelselectwindow.h"

LevelSelectWindow::LevelSelectWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LevelSelectWindow)
{
    ui->setupUi(this);
}

LevelSelectWindow::~LevelSelectWindow()
{
    delete ui;
}

