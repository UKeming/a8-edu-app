#include "celebrationwindow.h"
#include "ui_celebrationwindow.h"

CelebrationWindow::CelebrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CelebrationWindow)
{
    ui->setupUi(this);
}

CelebrationWindow::~CelebrationWindow()
{
    delete ui;
}
