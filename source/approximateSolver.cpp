#include "headers/approximateSolver.h"

QVector< QList<Job*> > approximateSolver::aproximateSequencing(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job*> > orderedJobs(MachineAmount);
    int* freeTimeOnMachine = new int[MachineAmount];

    int MachineToAssignJob = 0;

    for(int i=0; i<MachineAmount; ++i)
        freeTimeOnMachine[i] = 0;

    sortJobs(&jobs,1, &approximateSolver::DescendingBasedOnProcessingTime);

    for(int i=0; i < jobs.length(); ++i)
    {
        MachineToAssignJob = FindFreeMachine(freeTimeOnMachine, MachineAmount);

        orderedJobs[MachineToAssignJob].append(jobs[i]);

        freeTimeOnMachine[MachineToAssignJob] += jobs[i]->getTimeFromMachinePlotting(1);
    }

    delete[] freeTimeOnMachine;

    return orderedJobs;
}

int approximateSolver::FindFreeMachine(int* MachineTimes, int MachineAmount)
{
    if(MachineAmount == 1)
        return 0;
    else
    {
        int ret = 0;
        for(int i=1; i < MachineAmount; ++i)
        {
            if( MachineTimes[i] < MachineTimes[ret])
                ret = i;
        }
        return ret;
    }
}
