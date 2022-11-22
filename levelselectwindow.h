#ifndef LEVELSELECTWINDOW_H
#define LEVELSELECTWINDOW_H

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

private:
    Ui::LevelSelectWindow *ui;

private slots:
    void openLevel(const QModelIndex& level);
};
#endif // LEVELSELECTWINDOW_H
