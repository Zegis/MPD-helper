#include "headers\ploter.h"

Ploter::Ploter(): scale(20), labelOffset(24,4), jobHeight(19), lineStartingX(20)
{
    colorTab[0].setNamedColor("cyan");
    colorTab[1].setNamedColor("cyan");
    colorTab[2].setNamedColor("olive");
    colorTab[3].setNamedColor("chartreuse");
    colorTab[4].setNamedColor("chocolate");
    colorTab[5].setNamedColor("coral");
    colorTab[6].setNamedColor("crimson");
    colorTab[7].setNamedColor("olive");
    colorTab[8].setNamedColor("gold");
    colorTab[9].setNamedColor("fuchsia");
    colorTab[10].setNamedColor("tan");


    lineStartingY[0] = 20;
    lineStartingY[1] = 40;
    lineStartingY[2] = 60;
}

QGraphicsScene* Ploter::drawSolutionPlot(Machine** machines, int MachineCount, int JobCount)
{
    int * offsetForJob = new int[MachineCount];

    for(int i=0; i < MachineCount; ++i)
        offsetForJob[i] = 0;

    int currentMashineJobWidth = 0;

    int LabelsCount = JobCount * MachineCount;

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
        for(int j=0; j < MachineCount; ++j)
        {
            int jobId = machines[j]->getJobId(i);

            pen.setColor(colorTab[jobId]);
            brush.setColor(colorTab[jobId]);

            jobLabelContent.setNum(jobId);
            jobLabelContent.insert(0,"Z");

            currentMashineJobWidth = machines[j]->getJobDuration(i);

            if( j > 0 && offsetForJob[j-1] >= offsetForJob[j])
                offsetForJob[j] = offsetForJob[j-1];

            TimeLabels[labelIdxj]->setText(jobLabelContent);
            TimeLabels[labelIdxj]->setPos(labelOffset.x() + offsetForJob[j] * scale, lineStartingY[j] + labelOffset.y());

            plot.addRect(lineStartingX + offsetForJob[j] * scale, lineStartingY[j], currentMashineJobWidth * scale, jobHeight , pen, brush);
            plot.addItem(TimeLabels[labelIdxj++]);

            offsetForJob[j] += currentMashineJobWidth;
        }
    }

    PrepareAxis(offsetForJob[MachineCount-1], MachineCount);

    return &plot;
}

void Ploter::PrepareAxis(int maxTime, int MachineCount)
{
    QString tmp;
    QGraphicsSimpleTextItem **MashineLabels = new QGraphicsSimpleTextItem*[MachineCount];

    for(int i=0; i < MachineCount; ++i)
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

QGraphicsScene* Ploter::drawParallelPlot(Machine **machines, int MachineCount, int JobCount)
{
    int currentMashineJobWidth = 0;

    int LabelsCount = JobCount;

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
    int offsetForJob;
    int maxTime = 0;
    for(int j=0; j < MachineCount; ++j)
    {
        offsetForJob = 0;
        for(int i=1; i <= machines[j]->getNumberOfJobs(); ++i)
        {
            int jobId = machines[j]->getJobId(i);

            pen.setColor(colorTab[jobId]);
            brush.setColor(colorTab[jobId]);

            jobLabelContent.setNum(jobId);
            jobLabelContent.insert(0,"Z");

            currentMashineJobWidth = machines[j]->getJobDuration(i);

            TimeLabels[labelIdxj]->setText(jobLabelContent);
            TimeLabels[labelIdxj]->setPos(labelOffset.x() + offsetForJob * scale, lineStartingY[j] + labelOffset.y());

            plot.addRect(lineStartingX + offsetForJob * scale, lineStartingY[j], currentMashineJobWidth * scale, jobHeight , pen, brush);
            plot.addItem(TimeLabels[labelIdxj++]);

            offsetForJob += currentMashineJobWidth;
        }

        if(maxTime < machines[j]->getEndingTimeForLastJob()) maxTime = machines[j]->getEndingTimeForLastJob();
     }

    PrepareAxis(maxTime, MachineCount);

    return &plot;
}
