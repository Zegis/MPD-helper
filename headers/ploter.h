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
    QColor colorTab[10];

    QGraphicsScene plot;

    void PrepareLabels(int maxTime, int MashineCount);

};

#endif // PLOTER_H
