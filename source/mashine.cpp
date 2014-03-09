#include "headers/mashine.h"

Machine::Machine(int Id)
{
    id = Id;
}

Machine::Machine(int Id, QList<Job *> Jobs)
{
    id = Id;
    jobs = Jobs;
}

void Machine::appendJob(Job * newJob)
{
    jobs.append(newJob);
}

void Machine::setJobs(QList<Job *> Jobs)
{
    jobs = Jobs;
}

int Machine::getEndingTimeForJob(int jobNumber)
{
    --jobNumber;
    if(jobNumber >= 0 && jobNumber < jobs.count())
    {

        if(jobNumber != 0)
        {
            int retValue = 0;
            for(int i=0; i <= jobNumber; ++i)
                retValue += jobs[i]->getTimeFromMachinePlotting(id);

            return retValue;
        }
        else
        {
            return jobs[jobNumber]->getTimeFromMachinePlotting(id);
        }
    }
    else
        return 0;
}

int Machine::getJobDuration(int jobNumber)
{
    --jobNumber;
    if(jobNumber >= 0 && jobNumber < jobs.count())
    {

        return jobs[jobNumber]->getTimeFromMachinePlotting(id);
    }
    else
        return 0;
}

int Machine::getEndingTimeForLastJob()
{
    int retValue = 0;

    for(int i=0; i < jobs.count(); ++i)
        retValue += jobs[i]->getTimeFromMachine(id);

    return retValue;
}

void Machine::clear()
{
    jobs.clear();
}


int Machine::getJobId(int jobNumber)
{
    --jobNumber;
    return jobs[jobNumber]->getId();
}
