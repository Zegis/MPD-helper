#include "headers\ploter.h"

Ploter::Ploter()
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
}

QGraphicsScene* Ploter::drawSolutionPlot(Mashine* first, Mashine* second, Mashine* third, int JobCount, int MashineCount , QString result)
{
    int offsetFor2ndJob = first->getEndingTimeForJob(1);
    int offsetFor1stJob = 0;
    int offsetFor3rdJob = 0;
    int jobWidth = 0;
    int job2Width = 0;
    int job3Width = 0;

    int LabelsCount = JobCount * MashineCount;

    plot.clear();
    plot.setSceneRect(0,0,356,86);

    QPen pen(colorTab[0]);
    QBrush brush(colorTab[0]);

    QString tmp;
    QGraphicsSimpleTextItem **TimeLabels = new QGraphicsSimpleTextItem*[LabelsCount];

    plot.clear();

    for(int i=0; i < LabelsCount; ++i)
    {
        TimeLabels[i] = new QGraphicsSimpleTextItem();
    }

    int j=0;
    for(int i=1; i < JobCount+1; ++i)
    {

        tmp.setNum(first->getJobId(i));
        tmp.insert(0,"Z");

        jobWidth = first->getJobDuration(i);

        TimeLabels[j]->setText(tmp);
        TimeLabels[j]->setPos(24+offsetFor1stJob*20,25);
        plot.addRect(20+offsetFor1stJob*20,20,20*jobWidth,20,pen,brush);
        plot.addItem(TimeLabels[j++]);

        if(MashineCount != 1)
        {
        job2Width = second->getJobDuration(i);

        if( offsetFor1stJob + jobWidth >= offsetFor2ndJob)
            offsetFor2ndJob = offsetFor1stJob + jobWidth;

        TimeLabels[j]->setText(tmp);
        TimeLabels[j]->setPos(24+offsetFor2ndJob*20,45);
        plot.addRect(20+offsetFor2ndJob*20,40,20*job2Width,20,pen,brush);
        plot.addItem(TimeLabels[j++]);

        if(MashineCount == 3)
        {
        job3Width = third->getJobDuration(i);

        if( offsetFor2ndJob + job2Width >= offsetFor3rdJob)
            offsetFor3rdJob = offsetFor2ndJob + job2Width;

        TimeLabels[j]->setText(tmp);
        TimeLabels[j]->setPos(24+offsetFor3rdJob*20,65);
        plot.addRect(20+offsetFor3rdJob*20,60,20*job3Width,20,pen,brush);
        plot.addItem(TimeLabels[j++]);
        }
        }

        pen.setColor(colorTab[i]);
        brush.setColor(colorTab[i]);
        offsetFor1stJob = first->getEndingTimeForJob(i);

        offsetFor2ndJob += job2Width;
        offsetFor3rdJob += job3Width;
    }

    if(MashineCount == 3)
    {
        result.setNum(offsetFor3rdJob);
        PrepareLabels(offsetFor3rdJob, MashineCount);
    }
    else if(MashineCount == 2)
    {
        result.setNum(offsetFor2ndJob);
        PrepareLabels(offsetFor2ndJob, MashineCount);
    }
    else
    {
        result.setNum(offsetFor1stJob);
        PrepareLabels(offsetFor1stJob, MashineCount);
    }

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
        MashineLabels[i]->setPos(0,24+i*20);
        plot.addItem(MashineLabels[i]);

        tmp.clear();
    }

    QGraphicsSimpleTextItem **TimeLabels = new QGraphicsSimpleTextItem*[maxTime];
    for(int i=0; i < maxTime; ++i)
    {
        TimeLabels[i] = new QGraphicsSimpleTextItem();
        TimeLabels[i]->setText(tmp.setNum(i+1));
        TimeLabels[i]->setPos(24+i*20,0);
        plot.addItem(TimeLabels[i]);
    }
}
