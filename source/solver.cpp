#include "headers/solver.h"

Solver::Solver()
{
}

Solution Solver::Solve(QList<Job*> jobs, int MachineAmount)
{
    return Solution("Brak");
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
