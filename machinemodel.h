#ifndef MACHINEMODEL_H
#define MACHINEMODEL_H

#include <QObject>
#include <vector>
#include <map>
#include "constants.h"


class MachineModel : public QObject
{
    Q_OBJECT
public:
    explicit MachineModel(QObject *parent = nullptr);

private:



    int stateCount=1;

    // Map each QWidget to an ID
    std::map<int, std::tuple<ProgramBlock, QPoint>> map;


};

#endif // MACHINEMODEL_H
