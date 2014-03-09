#include "headers\ploter.h"

Ploter::Ploter(): scale(20), labelOffset(24,4), jobHeight(19), lineStartingX(20)
{
    colorTab[0].setNamedColor("cyan");
    colorTab[1].setNamedColor("olive");
    colorTab[2].setNamedColor("chartreuse");
    colorTab[3].setNamedColor("chocolate");
    colorTab[4].setNamedColor("coral");
    colorTab[5].setNamedColor("crimson");
    colorTab[6].setNamedColor("olive");
    colorTab[7].setNamedColor("gold");
    colorTab[7].setNamedColor("fuchsia");
    colorTab[9].setNamedColor("tan");

    lineStartingY[0] = 20;
    lineStartingY[1] = 40;
    lineStartingY[2] = 60;
}

QGraphicsScene* Ploter::drawSolutionPlot(Mashine** mashines, int MashineCount, int JobCount, QString result)
{
    int * offsetForJob = new int[MashineCount];

    for(int i=0; i < MashineCount; ++i)
        offsetForJob[i] = 0;

    int currentMashineJobWidth = 0;

    int LabelsCount = JobCount * MashineCount;

    plot.clear();
    plot.setSceneRect(0,0,356,86);

    QPen pen(colorTab[0]);
    QBrush brush(colorTab[0]);

    QString jobLabelContent;
    QGraphicsSimpleTextItem **TimeLabels = new QGraphicsSimpleTextItem*[LabelsCount];

    plot.clear();

    for(int i=0; i < LabelsCount; ++i)
    {
        TimeLabels[i] = new QGraphicsSimpleTextItem();
    }

    int labelIdxj=0;
    for(int i=1; i < JobCount+1; ++i)
    {
        for(int j=0; j < MashineCount; ++j)
        {
            jobLabelContent.setNum(mashines[j]->getJobId(i));
            jobLabelContent.insert(0,"Z");

            currentMashineJobWidth = mashines[j]->getJobDuration(i);

            if( i > 0 && offsetForJob[j-1] >= offsetForJob[j])
                offsetForJob[j] = offsetForJob[j-1];

            TimeLabels[labelIdxj]->setText(jobLabelContent);
            TimeLabels[labelIdxj]->setPos(labelOffset.x() + offsetForJob[j] * scale, lineStartingY[j] + labelOffset.y());

            plot.addRect(lineStartingX + offsetForJob[j] * scale, lineStartingY[j], currentMashineJobWidth * scale, jobHeight , pen, brush);
            plot.addItem(TimeLabels[labelIdxj++]);

            offsetForJob[j] += currentMashineJobWidth;
        }

        pen.setColor(colorTab[i]);
        brush.setColor(colorTab[i]);
    }

    result.setNum(offsetForJob[MashineCount-1]);
    PrepareLabels(offsetForJob[MashineCount-1], MashineCount);

    return &plot;
}

void Ploter::PrepareLabels(int maxTime, int MashineCount)
{
    QString tmp;
    QGraphicsSimpleTextItem **MashineLabels = new QGraphicsSimpleTextItem*[MashineCount];

    for(int i=0; i < MashineCount; ++i)
    {
        tmp.setNum(i+1);
        tmp.insert(0,"M");

        MashineLabels[i] = new QGraphicsSimpleTextItem();
        MashineLabels[i]->setText(tmp);
        MashineLabels[i]->setPos(2, 24 + i * scale);
        plot.addItem(MashineLabels[i]);

        tmp.clear();
    }

    QGraphicsSimpleTextItem **TimeLabels = new QGraphicsSimpleTextItem*[maxTime];
    for(int i=0; i < maxTime; ++i)
    {
        TimeLabels[i] = new QGraphicsSimpleTextItem();
        TimeLabels[i]->setText(tmp.setNum(i+1));
        TimeLabels[i]->setPos(24+ i * scale,0);
        plot.addItem(TimeLabels[i]);
    }
}
