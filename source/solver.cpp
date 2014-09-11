#include "headers/solver.h"

Solver::Solver()
{
}

Solution Solver::Solve(QList<Job*> jobs, int MachineAmount)
{
    return Solution("Brak");
}

Solution Solver::LPT(QList<Job *> jobs, int MachineAmount)
{
    return Solution(aproximateSequencing(jobs,MachineAmount));
}

QVector< QList<Job*> > Solver::aproximateSequencing(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job*> > orderedJobs(MachineAmount);
    int* freeTimeOnMachine = new int[MachineAmount];

    int MachineToAssignJob = 0;

    for(int i=0; i<MachineAmount; ++i)
        freeTimeOnMachine[i] = 0;

    sortJobs(&jobs,1, &Solver::DescendingBasedOnProcessingTime);

    for(int i=0; i < jobs.length(); ++i)
    {
        MachineToAssignJob = FindFreeMachine(freeTimeOnMachine, MachineAmount);

        orderedJobs[MachineToAssignJob].append(jobs[i]);

        freeTimeOnMachine[MachineToAssignJob] += jobs[i]->getTimeFromMachinePlotting(1);
    }

    delete[] freeTimeOnMachine;

    return orderedJobs;
}

Solution Solver::RPT(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job*> > orderedJobs = aproximateSequencing(jobs, MachineAmount);

    for(int i=0; i < orderedJobs.size(); ++i)
        sortJobs(&orderedJobs[i], 1, &Solver::AscendingBasedOnProcessingTime);

    return Solution(orderedJobs);
}

int Solver::FindFreeMachine(int* MachineTimes, int MachineAmount)
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

void Solver::sortJobs(QList<Job *> *JobsToSort, int MachineToCompare, int (Solver::* comparator)(Job *, Job *, int))
{
    int n = JobsToSort->size();
    do
    {
        for(int i=0; i < n-1; ++i)
        {
            if( (this->*comparator)( (*JobsToSort)[i], (*JobsToSort)[i+1], MachineToCompare) == 1)
                    JobsToSort->swap(i,i+1);
        }
        --n;
    }while(n > 1);
}

int Solver::AscendingBasedOnProcessingTime(Job* A, Job* B, int MachineToCompare)
{
    if( A->getTimeFromMachinePlotting(MachineToCompare) > B->getTimeFromMachinePlotting(MachineToCompare) )
        return 1;
    else
        return 0;
}

int Solver::DescendingBasedOnProcessingTime(Job *A, Job *B, int MachineToCompare)
{
    if( A->getTimeFromMachinePlotting(MachineToCompare) < B->getTimeFromMachinePlotting(MachineToCompare) )
        return 1;
    else
        return 0;
}

int Solver::AscendingBasedOnRelase(Job* A, Job* B, int def = 0)
{
    if( A->getRelaseTime() > B->getRelaseTime())
        return 1;
    else
        return 0;
}
