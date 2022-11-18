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
  const int CONDITIONAL_BLOCK_SIZE_X = 180, CONDITIONAL_BLOCK_SIZE_Y=30;
  const int INNER_BLOCK_SIZE_X = 80, INNER_BLOCK_SIZE_Y=20;
  const int INNER_BLOCK_SIZE_SMALLER_X = 30, INNER_BLOCK_SIZE_SMALLER_Y=20;

  const QColor beginBlockColor = QColor::fromRgb(0, 150, 0);

  const QColor ifBlockColor = QColor::fromRgb(100, 100, 100);

  const QColor whileBlockColor = QColor::fromRgb(100, 100, 200);

  const QColor generalBlockColor = QColor::fromRgb(150, 150, 150);

  std::map<int, std::tuple<ProgramBlock, QPointF, QPoint>> map;
  std::map<int, std::tuple<ProgramBlock, ProgramBlock>> condition;

  std::vector<int> blockTree;

  bool moving;
  bool connect;
  int stateCount = 1;

  int hoverBlock;
  int selectedBlock;
  ProgramBlock type;

  void paintEvent(QPaintEvent *event);

  void addBlock(ProgramBlock blockType, QPointF position);
  void connectBlock(int block1, int block2);

  void drawBlock(int blockID, QPainter& painter);
  void drawConnection(QPointF start, QPointF end, QPoint size,QPainter& painter);
  int getBlock(QPointF point);

  bool event(QEvent *event);
  void mousePressHandler(QMouseEvent* event);
  void mouseClickHandler(QMouseEvent* event);
  void mouseReleaseHandler(QMouseEvent* event);
  void mouseMoveHandler(QMouseEvent* event);
  const std::string getText(ProgramBlock p);

public slots:
  void setConnectState();
  void setType(ProgramBlock type);
  std::vector<ProgramBlock> getProgram();




signals:
};

#endif // MACHINEGRAPH_H
