#include "headers/job.h"

Job::Job(int Id, int NumberOfMashines)
{
    id = Id;
    numberOfMachines = NumberOfMashines;

    timesOnMachines = new int[numberOfMachines];

    for(int i=0; i<numberOfMachines; ++i)
        timesOnMachines[i] = 0;

    for(int i=0; i<3; ++i)
        proceedingJobs[i] = 0;
}

int Job::getId()
{
    return id;
}

void Job::setTimeOnMachine(int time, int machine)
{
    --machine;
    if(machine < numberOfMachines && machine >= 0)
    {
        timesOnMachines[machine] = time;
    }
}

int Job::getTimeFromMachine(int machine)
{
    --machine;
    if(machine < numberOfMachines && machine >= 0)
    {
        if(numberOfMachines != 3)
            return timesOnMachines[machine];
        else if(machine != 2)
        {
            return (timesOnMachines[machine] + timesOnMachines[machine+1]);
        }
    }

    return 0;
}

int Job::getTimeFromMachinePlotting(int machine)
{
    --machine;

    if(machine < numberOfMachines && machine >= 0)
    {
        return timesOnMachines[machine];
    }

    return timesOnMachines[0];
}

int Job::getJobDuration(int machine)
{
    --machine;

    if(machine < numberOfMachines && machine >= 0)
    {
        return timesOnMachines[machine];
    }

    return 0;
}

void Job::setRelaseTime(int relase)
{
    r = relase;
}

int Job::getRelaseTime()
{
    return r;
}

bool Job::proceeds(int id)
{
    for(int i=0; i<3; ++i)
        if(proceedingJobs[i] == id)
            return true;

    return false;
}

void Job::addProceedingJob(int id)
{
    for(int i=0; i<3; ++i)
        if(proceedingJobs[i] == 0)
            proceedingJobs[i] = id;
}

Job::~Job()
{
    delete [] timesOnMachines;
}
