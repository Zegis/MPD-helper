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

QGraphicsScene* Ploter::drawSolutionPlot(Mashine* first, Mashine* second, Mashine* third, int JobCount, int MashineCount , QString result)
{

    int offsetFor2ndJob = first->getEndingTimeForJob(1);
    int offsetFor1stJob = 0;
    int offsetFor3rdJob = 0;
    int jobWidth = 0;

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

    int j=0;
    for(int i=1; i < JobCount+1; ++i)
    {

        jobLabelContent.setNum(first->getJobId(i));
        jobLabelContent.insert(0,"Z");

        jobWidth = first->getJobDuration(i);

        TimeLabels[j]->setText(jobLabelContent);
        TimeLabels[j]->setPos(labelOffset.x() + offsetFor1stJob * scale, lineStartingY[0] + labelOffset.y());
        plot.addRect(lineStartingX + offsetFor1stJob * scale, lineStartingY[0], jobWidth * scale, jobHeight , pen, brush);
        plot.addItem(TimeLabels[j++]);

        offsetFor1stJob += jobWidth;

        if(MashineCount != 1)
        {
            jobWidth = second->getJobDuration(i);

            if( offsetFor1stJob >= offsetFor2ndJob)
                offsetFor2ndJob = offsetFor1stJob;

            TimeLabels[j]->setText(jobLabelContent);
            TimeLabels[j]->setPos(labelOffset.x() + offsetFor2ndJob * scale, lineStartingY[1] + labelOffset.y());
            plot.addRect(lineStartingX + offsetFor2ndJob * scale, lineStartingY[1],jobWidth * scale, jobHeight , pen, brush);
            plot.addItem(TimeLabels[j++]);

            offsetFor2ndJob += jobWidth;

            if(MashineCount == 3)
            {
                jobWidth = third->getJobDuration(i);

                if( offsetFor2ndJob >= offsetFor3rdJob)
                    offsetFor3rdJob = offsetFor2ndJob;

                TimeLabels[j]->setText(jobLabelContent);
                TimeLabels[j]->setPos(labelOffset.x() + offsetFor3rdJob * scale, lineStartingY[2] + labelOffset.y());
                plot.addRect(lineStartingX + offsetFor3rdJob * scale, lineStartingY[2],jobWidth * scale, jobHeight , pen, brush);
                plot.addItem(TimeLabels[j++]);

                offsetFor3rdJob += jobWidth;
            }
        }

        pen.setColor(colorTab[i]);
        brush.setColor(colorTab[i]);
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
