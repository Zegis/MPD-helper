#ifndef PLOTER_H
#define PLOTER_H

#include<QGraphicsScene>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include "mashine.h"

class Ploter
{    
public:
    Ploter();

    QGraphicsScene* drawSolutionPlot(Machine ** machines, int MachineCount, int JobCount);
    QGraphicsScene* drawParallelPlot(Machine ** machines, int MachineCount, int JobCount);

private:

    const int scale;
    const QPointF labelOffset;
    const int jobHeight;
    const int lineStartingX;


    QColor colorTab[10];

    int lineStartingY[3];

    QGraphicsScene plot;

    void PrepareAxis(int maxTime, int MachineCount);

};

#endif // PLOTER_H
