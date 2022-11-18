#ifndef MACHINEEDITOR_H
#define MACHINEEDITOR_H

#include <QMainWindow>
#include "constants.h"
namespace Ui {
class MachineEditor;
}

class MachineEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MachineEditor(QWidget *parent = nullptr);
    ~MachineEditor();


private:
    Ui::MachineEditor *ui;

public slots:

private slots:
    void ifButtonPushed();
    void notButtonPushed();
    void facingWallButtonPushed();
    void moveForwardButtonPushed();
    void turnLeftButtonPushed();
    void turnRightButtonPushed();
    void facingPitButtonPushed();
    void eatCheeseButtonPushed();
    void endWhileButtonPushed();
    void endIfButtonPushed();
    void whilePushed();
    void facingBlockButtonPushed();
    void facingCheeseButtonPushed();
signals:
    void changeType(ProgramBlock p);
};

#endif // MACHINEEDITOR_H
