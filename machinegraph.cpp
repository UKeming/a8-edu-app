#include "machinegraph.h"
#include <QEvent>
#include <QLine>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include <QPen>
#include <tuple>
#include <vector>
MachineGraph::MachineGraph(QWidget *parent) : QWidget{parent} {
  blockTree.push_back(-1);
  this->setAttribute(Qt::WA_Hover, true);

  map[0] = std::tuple<ProgramBlock, QPointF, QPoint>(
      ProgramBlock::begin, QPointF(0, 0),
      QPoint(GENERAL_BLOCK_SIZE_X, GENERAL_BLOCK_SIZE_Y));
  type = ProgramBlock::moveForward;
  selectedBlock = -1;
  hoverBlock = -1;
  connect = false;
  update();
}

void MachineGraph::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  for (const auto &[key, value] : map) {
    bool visited[blockTree.size()];

    for (auto i = 0; i < blockTree.size(); i++) {
      visited[i] = false;
    }

    painter.setPen(QPen(QColor::fromRgb(0, 0, 0), 2, Qt::SolidLine,
                        Qt::RoundCap, Qt::RoundJoin));

    int currentBlock = key;
    while (currentBlock != -1) {
      int next = blockTree[currentBlock];
      if (!visited[currentBlock]) {
        QPointF startPoint = std::get<QPointF>(map[currentBlock]);
        QPointF startSize = std::get<QPoint>(map[currentBlock]);
        visited[currentBlock] = true;
        if (next != -1) {
          QPoint endSize = std::get<QPoint>(map[next]);
          QPointF endPoint = std::get<QPointF>(map[next]);
          drawConnection(startPoint + startSize / 2, endPoint + endSize / 2,
                         endSize, painter);
        }
      }
      drawBlock(currentBlock, painter);
      currentBlock = next;
    }
  }
}

void MachineGraph::drawBlock(int blockID, QPainter &painter) {
  QPointF startPoint = std::get<QPointF>(map[blockID]);
  ProgramBlock type = std::get<ProgramBlock>(map[blockID]);
  QPoint size = std::get<QPoint>(map[blockID]);

  bool lighter;
  if (blockID == hoverBlock || blockID == selectedBlock) {
    lighter = true;
  }

  //  if ((blockID == hoverBlock && blockID == selectedBlock) ||
  //      ((blockID == hoverBlock) && (blockTree[hoverBlock] == selectedBlock)))
  //      {
  //    lightUp = 0;
  //  }
  if (blockID == hoverBlock && blockID == selectedBlock) {
    lighter = false;
  }

  int midY = startPoint.y() + size.y() / 2;
  int midX = startPoint.x() + size.x() / 2;

  QColor blockColor;
  QColor innerBlockColor;

  if (type == ProgramBlock::begin) {
    blockColor = beginBlockColor;

  } else if (type == ProgramBlock::ifStatement || type == ProgramBlock::endIf) {
    blockColor = ifBlockColor;

  } else if (type == ProgramBlock::whileLoop ||
             type == ProgramBlock::endWhile) {
    blockColor = whileBlockColor;

  } else {
    blockColor = generalBlockColor;
  }
  innerBlockColor = blockColor.lighter().lighter();

  if (lighter) {
    blockColor = blockColor.lighter();
    innerBlockColor = innerBlockColor.lighter();
  }

  switch (type) {
  case ProgramBlock::ifStatement: {
    painter.fillRect(startPoint.x(), startPoint.y(), CONDITIONAL_BLOCK_SIZE_X,
                     CONDITIONAL_BLOCK_SIZE_Y, blockColor);
    painter.drawText(startPoint.x() + 5, midY, this->getText(type).c_str());
    ProgramBlock firstConst = std::get<0>(condition[blockID]);
    ProgramBlock secondConst = std::get<1>(condition[blockID]);
    painter.fillRect(startPoint.x() + 20, midY - INNER_BLOCK_SIZE_SMALLER_Y / 2,
                     INNER_BLOCK_SIZE_SMALLER_X, INNER_BLOCK_SIZE_SMALLER_Y,
                     innerBlockColor);
    painter.drawText(startPoint.x() + 20, midY,
                     this->getText(firstConst).c_str());

    painter.fillRect(startPoint.x() + 30 + INNER_BLOCK_SIZE_SMALLER_X,
                     midY - INNER_BLOCK_SIZE_Y / 2, INNER_BLOCK_SIZE_X,
                     INNER_BLOCK_SIZE_Y, innerBlockColor);
    painter.drawText(startPoint.x() + 30 + INNER_BLOCK_SIZE_SMALLER_X, midY,
                     this->getText(secondConst).c_str());
    break;
  }
  case ProgramBlock::whileLoop: {
    painter.fillRect(startPoint.x(), startPoint.y(), CONDITIONAL_BLOCK_SIZE_X,
                     CONDITIONAL_BLOCK_SIZE_Y, blockColor);
    painter.drawText(startPoint.x() + 5, midY, this->getText(type).c_str());
    ProgramBlock firstConst = std::get<0>(condition[blockID]);
    ProgramBlock secondConst = std::get<1>(condition[blockID]);
    painter.fillRect(startPoint.x() + 50, midY - INNER_BLOCK_SIZE_SMALLER_Y / 2,
                     INNER_BLOCK_SIZE_SMALLER_X, INNER_BLOCK_SIZE_SMALLER_Y,
                     innerBlockColor);
    painter.drawText(startPoint.x() + 50, midY,
                     this->getText(firstConst).c_str());

    painter.fillRect(startPoint.x() + 60 + INNER_BLOCK_SIZE_SMALLER_X,
                     midY - INNER_BLOCK_SIZE_Y / 2, INNER_BLOCK_SIZE_X,
                     INNER_BLOCK_SIZE_Y, innerBlockColor);
    painter.drawText(startPoint.x() + 60 + INNER_BLOCK_SIZE_SMALLER_X, midY,
                     this->getText(secondConst).c_str());
    break;
  }
  default: {
    painter.fillRect(startPoint.x(), startPoint.y(), size.x(),
                     GENERAL_BLOCK_SIZE_Y, blockColor);
    QFontMetrics fm(painter.font());
    const std::string str = this->getText(type);
    int xoffset = fm.boundingRect(str.c_str()).width() / 2;
    painter.drawText(midX - xoffset, midY, str.c_str());
  }
  }
}

void MachineGraph::drawConnection(QPointF start, QPointF end, QPoint size,
                                  QPainter &painter) {

  float distX = qAbs(end.x() - start.x());
  float distY = qAbs(end.y() - start.y());
  int arrowSize = 5;
  if (distY < distX) {
    painter.drawLine(QLine(start.x(), start.y(), start.x(), end.y()));
    painter.drawLine(QLine(start.x(), end.y(), end.x(), end.y()));
    // Arrow points left.
    //    if (start.x() > end.x() - size.x() / 2 &&
    //        start.x() < end.x() + size.x() / 2) {
    //      if (end.y() > start.y()) {
    //        QPainterPath path;
    //        path.moveTo(start.x(), end.y() - size.y() / 2);
    //        path.lineTo(start.x() - arrowSize, end.y() - size.y() / 2 -
    //        arrowSize); path.lineTo(start.x() + arrowSize, end.y() - size.y()
    //        / 2 - arrowSize); painter.fillPath(path, QColor::fromRgb(0, 0,
    //        0));
    //      } else {
    //        QPainterPath path;
    //        path.moveTo(start.x(), end.y() + size.y() / 2);
    //        path.lineTo(start.x() - arrowSize, end.y() + size.y() / 2 +
    //        arrowSize); path.lineTo(start.x() + arrowSize, end.y() + size.y()
    //        / 2 + arrowSize); painter.fillPath(path, QColor::fromRgb(0, 0,
    //        0));
    //      }
    //      return;
    //    }
    if (end.x() < start.x()) {
      QPainterPath path;
      path.moveTo(end.x() + size.x() / 2, end.y());
      path.lineTo(end.x() + size.x() / 2 + arrowSize, end.y() - arrowSize);
      path.lineTo(end.x() + size.x() / 2 + arrowSize, end.y() + arrowSize);
      painter.fillPath(path, QColor::fromRgb(0, 0, 0));
    } else {
      QPainterPath path;
      path.moveTo(end.x() - size.x() / 2, end.y());
      path.lineTo(end.x() - size.x() / 2 - arrowSize, end.y() - arrowSize);
      path.lineTo(end.x() - size.x() / 2 - arrowSize, end.y() + arrowSize);
      painter.fillPath(path, QColor::fromRgb(0, 0, 0));
    }
  } else {
    painter.drawLine(QLine(start.x(), start.y(), end.x(), start.y()));
    painter.drawLine(QLine(end.x(), start.y(), end.x(), end.y()));

    //    if (start.y() > end.y() - size.y() / 2 &&
    //        start.y() < end.y() + size.y() / 2) {
    //      if (end.x() > start.x()) {
    //        QPainterPath path;
    //        path.moveTo(end.x() - size.x() / 2, start.y());
    //        path.lineTo(end.x() - size.x() / 2 - arrowSize, start.y() -
    //        arrowSize); path.lineTo(end.x() - size.x() / 2 - arrowSize,
    //        start.y() + arrowSize); painter.fillPath(path, QColor::fromRgb(0,
    //        0, 0));
    //      } else {
    //        QPainterPath path;
    //        path.moveTo(end.x() + size.x() / 2, start.y());
    //        path.lineTo(end.x() + size.x() / 2 + arrowSize, start.y() -
    //        arrowSize); path.lineTo(end.x() + size.x() / 2 + arrowSize,
    //        start.y() + arrowSize); painter.fillPath(path, QColor::fromRgb(0,
    //        0, 0));
    //      }
    //      return;
    //    }
    if (end.y() < start.y()) {
      QPainterPath path;
      path.moveTo(end.x(), end.y() + size.y() / 2);
      path.lineTo(end.x() + arrowSize, end.y() + size.y() / 2 + arrowSize);
      path.lineTo(end.x() - arrowSize, end.y() + size.y() / 2 + arrowSize);
      painter.fillPath(path, QColor::fromRgb(0, 0, 0));
    } else {
      QPainterPath path;
      path.moveTo(end.x(), end.y() - size.y() / 2);
      path.lineTo(end.x() + arrowSize, end.y() - size.y() / 2 - arrowSize);
      path.lineTo(end.x() - arrowSize, end.y() - size.y() / 2 - arrowSize);
      painter.fillPath(path, QColor::fromRgb(0, 0, 0));
    }
  }
}
void MachineGraph::connectBlock(int block1, int block2) {
  if (blockTree[block2] != block1 && block2 != block1) {
    blockTree[block1] = block2;
  }
}

void MachineGraph::setConnectState() { connect = !connect; }

bool MachineGraph::event(QEvent *event) {
  switch (event->type()) {
  case QEvent::MouseButtonDblClick:
    mouseClickHandler(static_cast<QMouseEvent *>(event));
    return false;
    break;
  case QEvent::MouseButtonPress:
    mousePressHandler(static_cast<QMouseEvent *>(event));
    return false;
    break;
  case QEvent::MouseButtonRelease:
    mouseReleaseHandler(static_cast<QMouseEvent *>(event));
    return false;
    break;
  case QEvent::MouseMove:
    mouseMoveHandler(static_cast<QMouseEvent *>(event));
    return false;
    break;
  default:
    break;
  }
  QWidget::event(event);
  return false;
}
void MachineGraph::mouseMoveHandler(QMouseEvent *event) {
  if (moving && selectedBlock != -1 && !connect) {
    QPoint size = std::get<QPoint>(map[selectedBlock]);
    std::get<QPointF>(map[selectedBlock]) = event->position() - size / 2;
  }
  if (connect) {
    int blockId = getBlock(event->position());
    hoverBlock = blockId;
  }
  update();
}
void MachineGraph::mouseReleaseHandler(QMouseEvent *event) {
  if (selectedBlock == -1)
    return;
  if (connect) {
    int blockId = getBlock(event->position());
    if (blockTree[blockId] != selectedBlock) {
      connectBlock(selectedBlock, blockId);
    }
  }
  hoverBlock = -1;
  selectedBlock = -1;
  moving = false;
  update();
}
void MachineGraph::mousePressHandler(QMouseEvent *event) {
  int blockId = getBlock(event->position());
  if (blockId != -1) {
    selectedBlock = blockId;
  }
  moving = true;
  update();
}

void MachineGraph::mouseClickHandler(QMouseEvent *event) {
  if (Qt::LeftButton && event->position().x() > 0 &&
      event->position().y() > 0) {
    addBlock(type, event->position());
    update();
  }
}
const std::string MachineGraph::getText(ProgramBlock p) {
  switch (p) {
  case ProgramBlock::conditionFacingBlock:
    return "Facing Block";
  case ProgramBlock::conditionNot:
    return "Not";
  case ProgramBlock::conditionFacingPit:
    return "Facing Pit";
  case ProgramBlock::conditionFacingWall:
    return "Facing Wall";
  case ProgramBlock::conditionFacingCheese:
    return "Facing Cheese";
  case ProgramBlock::begin:
    return "Begin";
  case ProgramBlock::blank:
    return "";
  case ProgramBlock::eatCheese:
    return "Eat Chese";
  case ProgramBlock::endIf:
    return "End If";
  case ProgramBlock::endWhile:
    return "End While";
  case ProgramBlock::whileLoop:
    return "While";
  case ProgramBlock::ifStatement:
    return "If";
  case ProgramBlock::turnLeft:
    return "Turn Left";
  case ProgramBlock::turnRight:
    return "Turn Right";
  case ProgramBlock::moveForward:
    return "Move Forward";
  }
}

void MachineGraph::addBlock(ProgramBlock type, QPointF position) {
  if (type == ProgramBlock::conditionFacingBlock ||
      type == ProgramBlock::conditionFacingPit ||
      type == ProgramBlock::conditionFacingWall ||
      type == ProgramBlock::conditionFacingCheese ||
      type == ProgramBlock::conditionNot) {

    int blockId = getBlock(position);
    ProgramBlock blockType = std::get<ProgramBlock>(map[blockId]);
    if (blockType == ProgramBlock::whileLoop ||
        blockType == ProgramBlock::ifStatement) {
      if (type == ProgramBlock::conditionNot) {
        std::get<0>(condition[blockId]) = type;
      } else {
        std::get<1>(condition[blockId]) = type;
      }
    }
    return;
  }
  int id = blockTree.size();
  blockTree.push_back(-1);
  if (type == ProgramBlock::ifStatement || type == ProgramBlock::whileLoop) {
    map[id] = std::tuple<ProgramBlock, QPointF, QPoint>(
        type, position,
        QPoint(CONDITIONAL_BLOCK_SIZE_X, CONDITIONAL_BLOCK_SIZE_Y));
    condition[id] = std::tuple<ProgramBlock, ProgramBlock>(ProgramBlock::blank,
                                                           ProgramBlock::blank);
  } else {
    map[id] = std::tuple<ProgramBlock, QPointF, QPoint>(
        type, position, QPoint(GENERAL_BLOCK_SIZE_X, GENERAL_BLOCK_SIZE_Y));
  }
}

int MachineGraph::getBlock(QPointF point) {
  for (const auto &[key, value] : map) {
    QPointF startPoint = std::get<QPointF>(map[key]);
    QPoint size = std::get<QPoint>(map[key]);
    if (point.x() < (startPoint.x() + size.x()) && point.x() > startPoint.x() &&
        point.y() < (startPoint.y() + size.y()) && point.y() > startPoint.y()) {
      return key;
    }
  }

  return -1;
}
void MachineGraph::setType(ProgramBlock type) { this->type = type; }

std::vector<ProgramBlock> MachineGraph::getProgram() {
  int currentBlock = 0;
  std::vector<ProgramBlock> program;
  std::vector<ProgramBlock> grammaStack;
  while (currentBlock != -1) {
    int next = blockTree[currentBlock];
    ProgramBlock type = std::get<ProgramBlock>(map[currentBlock]);
    program.push_back(type);
    if (type == ProgramBlock::ifStatement || type == ProgramBlock::whileLoop) {
      grammaStack.push_back(type);
      ProgramBlock firstConst = std::get<0>(condition[currentBlock]);
      ProgramBlock secondConst = std::get<1>(condition[currentBlock]);
      if (secondConst == ProgramBlock::blank) {
        qDebug() << "Incomplete If Statement.";
        return std::vector<ProgramBlock>(ProgramBlock::blank);
      } else {
        program.push_back(firstConst);
        program.push_back(secondConst);
      }
    }

    if (type == ProgramBlock::endIf) {
      if (grammaStack.empty() ||
          grammaStack.back() != ProgramBlock::ifStatement) {
        qDebug() << "Invalid Syntax.";
        return std::vector<ProgramBlock>(ProgramBlock::blank);
      } else {
        grammaStack.pop_back();
      }
    }

    if (type == ProgramBlock::endWhile) {
      if (grammaStack.empty() ||
          grammaStack.back() != ProgramBlock::whileLoop) {
        qDebug() << "Invalid Syntax.";
        return std::vector<ProgramBlock>(ProgramBlock::blank);
      } else {
        grammaStack.pop_back();
      }
    }

    currentBlock = next;
  }

  if (!grammaStack.empty()) {
    qDebug() << "Invalid Syntax.";
    return std::vector<ProgramBlock>(ProgramBlock::blank);
  }
  qDebug() << program;

  return program;
}
