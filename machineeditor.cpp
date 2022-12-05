#include "machineeditor.h"
#include "machinegraph.h"
#include "ui_machineeditor.h"
#include <QCursor>
MachineEditor::MachineEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MachineEditor) {
  ui->setupUi(this);
  MachineGraph *graph = new MachineGraph();
  ui->mainLayout->insertWidget(0, graph);
  connect(ui->connectButton, &QPushButton::clicked, graph,
          &MachineGraph::toggleConnecting);
  connect(ui->resetBegin, &QPushButton::clicked, graph,
          &MachineGraph::resetBegin);

  connect(graph, &MachineGraph::connectToggled, this,
          &MachineEditor::connectToggled);

  connect(ui->ifButton, &QPushButton::clicked, this,
          &MachineEditor::ifButtonPushed);
  connect(ui->facingWallButton, &QPushButton::clicked, this,
          &MachineEditor::facingWallButtonPushed);
  connect(ui->notButton, &QPushButton::clicked, this,
          &MachineEditor::notButtonPushed);
  connect(ui->moveForward, &QPushButton::clicked, this,
          &MachineEditor::moveForwardButtonPushed);
  connect(ui->turnLeftButton, &QPushButton::clicked, this,
          &MachineEditor::turnLeftButtonPushed);
  connect(ui->turnRightButton, &QPushButton::clicked, this,
          &MachineEditor::turnRightButtonPushed);
  connect(ui->facingPitButton, &QPushButton::clicked, this,
          &MachineEditor::facingPitButtonPushed);
  connect(ui->eatCheeseButton, &QPushButton::clicked, this,
          &MachineEditor::eatCheeseButtonPushed);
  connect(ui->endWhileButton, &QPushButton::clicked, this,
          &MachineEditor::endWhileButtonPushed);
  connect(ui->endIfButton, &QPushButton::clicked, this,
          &MachineEditor::endIfButtonPushed);
  connect(ui->whileButton, &QPushButton::clicked, this,
          &MachineEditor::whilePushed);
  connect(ui->facingBlock, &QPushButton::clicked, this,
          &MachineEditor::facingBlockButtonPushed);
  connect(ui->facingCheese, &QPushButton::clicked, this,
          &MachineEditor::facingCheeseButtonPushed);

  connect(ui->getOutput, &QPushButton::clicked, graph,
          &MachineGraph::getProgram);

  // Get program from the graph and send it to the game window
  connect(graph, &MachineGraph::programData, this, &MachineEditor::emitProgram);

  connect(this, &MachineEditor::changeType, graph, &MachineGraph::setType);

  connect(this, &MachineEditor::changeType, graph, &MachineGraph::setType);
}

MachineEditor::~MachineEditor() { delete ui; }
void MachineEditor::ifButtonPushed() {
  emit changeType(ProgramBlock::ifStatement);
}
void MachineEditor::facingWallButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingWall);
}
void MachineEditor::notButtonPushed() {
  emit changeType(ProgramBlock::conditionNot);
}
void MachineEditor::moveForwardButtonPushed() {
  emit changeType(ProgramBlock::moveForward);
}
void MachineEditor::turnLeftButtonPushed() {
  emit changeType(ProgramBlock::turnLeft);
}
void MachineEditor::turnRightButtonPushed() {
  emit changeType(ProgramBlock::turnRight);
}
void MachineEditor::facingPitButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingPit);
}
void MachineEditor::eatCheeseButtonPushed() {
  emit changeType(ProgramBlock::eatCheese);
}
void MachineEditor::endWhileButtonPushed() {
  emit changeType(ProgramBlock::endWhile);
}
void MachineEditor::endIfButtonPushed() {
  emit changeType(ProgramBlock::endIf);
}
void MachineEditor::whilePushed() { emit changeType(ProgramBlock::whileLoop); }
void MachineEditor::facingBlockButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingBlock);
}
void MachineEditor::facingCheeseButtonPushed() {
  emit changeType(ProgramBlock::conditionFacingCheese);
}

void MachineEditor::connectToggled(bool connecting) {
  if (connecting) {
    ui->connectButton->setStyleSheet("background-color: rgb(255, 0, 0);font: "
                                     "700 9pt \"Microsoft YaHei UI\";");
    ui->connectButton->setText("Cancel");
  } else {
    ui->connectButton->setStyleSheet("font: 700 9pt \"Microsoft YaHei UI\";");
    ui->connectButton->setText("Connect Blocks");
  }
}

void MachineEditor::emitProgram(std::vector<ProgramBlock> program){
    emit programData(program);
}

