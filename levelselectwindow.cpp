#include "levelselectwindow.h"
#include "ui_levelselectwindow.h"
#include "constants.h"
#include "gamewindow.h"
#include "gamemodel.h"

LevelSelectWindow::LevelSelectWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LevelSelectWindow)
{
    ui->setupUi(this);

    for(size_t i = 1; i <= (sizeof(levels) / sizeof(std::vector<std::vector<MapTile>>)); i++) {
        ui->levelListWidget->addItem(QString("Level %1").arg(i));
    }

    connect(ui->levelListWidget, &QListWidget::clicked, this, &LevelSelectWindow::openLevel);

}

LevelSelectWindow::~LevelSelectWindow()
{
    delete ui;
}

void LevelSelectWindow::openLevel(const QModelIndex& level) {
    int selectedLevel = level.row();
    GameModel model(selectedLevel);
    GameWindow* window = new GameWindow(model);
    window->changeMap(levels[selectedLevel]);
    window->show();
    this->close();
}

