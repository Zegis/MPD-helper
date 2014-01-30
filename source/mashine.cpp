#include "headers/mashine.h"

Mashine::Mashine(int Id)
{
    id = Id;
}

Mashine::Mashine(int Id, QList<Job *> Jobs)
{
    id = Id;
    jobs = Jobs;
}

void Mashine::appendJob(Job * newJob)
{
    jobs.append(newJob);
}

void Mashine::setJobs(QList<Job *> Jobs)
{
    jobs = Jobs;
}

QString Mashine::getOrder()
{
    QString order, tmp;

    for(int i=0; i < jobs.size(); ++i)
    {
        tmp.setNum(jobs[i]->getId());
        order.append(tmp);
    }

    return order;
}

int Mashine::getEndingTimeForJob(int jobNumber)
{
    --jobNumber;
    if(jobNumber >= 0 && jobNumber < jobs.count())
    {

        if(jobNumber != 0)
        {
            int retValue = 0;
            for(int i=0; i <= jobNumber; ++i)
                retValue += jobs[i]->getTimeFromMashinePlotting(id);

            return retValue;
        }
        else
        {
            return jobs[jobNumber]->getTimeFromMashinePlotting(id);
        }
    }
    else
        return 0;
}

int Mashine::getJobDuration(int jobNumber)
{
    --jobNumber;
    if(jobNumber >= 0 && jobNumber < jobs.count())
    {

        return jobs[jobNumber]->getTimeFromMashinePlotting(id);
    }
    else
        return 0;
}

int Mashine::getEndingTimeForLastJob()
{
    int retValue = 0;

    for(int i=0; i < jobs.count(); ++i)
        retValue += jobs[i]->getTimeFromMashine(id);

    return retValue;
}

void Mashine::clear()
{
    jobs.clear();
}


int Mashine::getJobId(int jobNumber)
{
    --jobNumber;
    return jobs[jobNumber]->getId();
}
