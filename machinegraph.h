#ifndef MACHINEGRAPH_H
#define MACHINEGRAPH_H

#include "constants.h"
#include <QWidget>

class MachineGraph : public QWidget {
  Q_OBJECT
public:
  explicit MachineGraph(QWidget *parent = nullptr);

private:

  const int GENERAL_BLOCK_SIZE_X = 90, GENERAL_BLOCK_SIZE_Y=30;
  const int CONDITIONAL_BLOCK_SIZE_X = 200, CONDITIONAL_BLOCK_SIZE_Y=30;
  const int INNER_BLOCK_SIZE_X = 90, INNER_BLOCK_SIZE_Y=20;
  const int INNER_BLOCK_SIZE_SMALLER_X = 40, INNER_BLOCK_SIZE_SMALLER_Y=20;

  const QColor beginBlockColor = QColor::fromRgb(89, 255, 160);

  const QColor ifBlockColor = QColor::fromRgb(55, 114, 255);

  const QColor whileBlockColor = QColor::fromRgb(255, 252, 49);

  const QColor generalBlockColor = QColor::fromRgb(57, 62, 65);

  const QColor errorBlockColor = QColor::fromRgb(233, 79, 55);

  std::map<int, std::tuple<ProgramBlock, QPointF, QPoint>> map;
  std::map<int, std::tuple<ProgramBlock, ProgramBlock>> condition;

  std::vector<int> blockTree;

  bool moving;
  bool connecting;
  int stateCount = 1;
  QPointF pressedMousePosition, pressedBlockPosition;
  std::string errorMessage;

  int hoverBlock;
  int selectedBlock;
  ProgramBlock type;

  int currentRunningBlock, errorBlock;

  void paintEvent(QPaintEvent *event);

  void addBlock(ProgramBlock blockType, QPointF position);
  void connectBlock(int block1, int block2);

  void drawBlock(int blockID, QPainter& painter);
  void drawConnection(ProgramBlock type, QPointF start, QPointF end, QPoint size,QPainter& painter);
  void drawTextFromMid(QPointF position, std::string text, QPainter& painter);

  void setErrorMessage(int blockId, std::string message);
  int getBlock(QPointF point);

  bool event(QEvent *event);
  void mousePressHandler(QMouseEvent* event);
  void mouseClickHandler(QMouseEvent* event);
  void mouseReleaseHandler(QMouseEvent* event);
  void mouseMoveHandler(QMouseEvent* event);
  const std::string getText(ProgramBlock p);

public slots:
  void toggleConnecting();
  void setType(ProgramBlock type);
  std::vector<ProgramBlock> getProgram();




signals:
  void connectToggled(bool connecting);
};

#endif // MACHINEGRAPH_H
