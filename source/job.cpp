#include "headers/job.h"

Job::Job(int Id, int NumberOfMashines)
{
    id = Id;
    numberOfMashines = NumberOfMashines;

    timesOnMashines = new int[numberOfMashines];

    for(int i=0; i<numberOfMashines; ++i)
        timesOnMashines[i] = 0;
}

int Job::getId()
{
    return id;
}

void Job::setTimeOnMashine(int time, int mashine)
{
    --mashine;
    if(mashine < numberOfMashines && mashine >= 0)
    {
        timesOnMashines[mashine] = time;
    }
}

int Job::getTimeFromMashine(int mashine)
{
    --mashine;
    if(mashine < numberOfMashines && mashine >= 0)
    {
        if(numberOfMashines != 3)
            return timesOnMashines[mashine];
        else if(mashine != 2)
        {
            return (timesOnMashines[mashine] + timesOnMashines[mashine+1]);
        }
    }

    return 0;
}

int Job::getTimeFromMashinePlotting(int mashine)
{
    --mashine;

    if(mashine < numberOfMashines && mashine >= 0)
    {
        return timesOnMashines[mashine];
    }

    return 0;
}

Job::~Job()
{
    delete [] timesOnMashines;
}
