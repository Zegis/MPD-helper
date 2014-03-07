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

    QGraphicsScene* drawSolutionPlot(Mashine *first, Mashine *second, Mashine *third, int JobCount, int MashineCount, QString result);

private:

    const int scale;
    const QPointF labelOffset;
    const int jobHeight;
    const int lineStartingX;


    QColor colorTab[10];

    int lineStartingY[3];

    QGraphicsScene plot;

    void PrepareLabels(int maxTime, int MashineCount);

};

#endif // PLOTER_H
