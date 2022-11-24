#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "gamemodel.h"
#include "machineeditor.h"

GameWindow::GameWindow(GameModel& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    MachineEditor* editor = new MachineEditor();
    editor->show();
}

GameWindow::~GameWindow()
{
    delete ui;
}
