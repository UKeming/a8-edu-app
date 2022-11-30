#ifndef LEVELSELECTWINDOW_H
#define LEVELSELECTWINDOW_H

#include "constants.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LevelSelectWindow; }
QT_END_NAMESPACE

class LevelSelectWindow : public QMainWindow
{
    Q_OBJECT

public:
    LevelSelectWindow(QWidget *parent = nullptr);
    ~LevelSelectWindow();

signals:
    void selectLevel(std::vector<std::vector<MapTile>>);

private:
    Ui::LevelSelectWindow *ui;

private slots:
    void openLevel(const QModelIndex& level);
};
#endif // LEVELSELECTWINDOW_H
