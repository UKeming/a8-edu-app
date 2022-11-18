#ifndef CELEBRATIONWINDOW_H
#define CELEBRATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class CelebrationWindow;
}

class CelebrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CelebrationWindow(QWidget *parent = nullptr);
    ~CelebrationWindow();

private:
    Ui::CelebrationWindow *ui;
};

#endif // CELEBRATIONWINDOW_H
