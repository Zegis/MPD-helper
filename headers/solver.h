#ifndef SOLVER_H
#define SOLVER_H

#include "job.h"
#include "solution.h"
#include <QList>
#include <QVector>

class Solver
{    
public:
    Solver();

    virtual Solution Solve(QList<Job*> jobs, int MachineAmount);

protected:

    int AscendingBasedOnProcessingTime(Job *A, Job *B, int MachineToCompare);

    int DescendingBasedOnProcessingTime(Job* A, Job* B, int MachineToCompare);

    int AscendingBasedOnRelase(Job* A, Job* B, int def);

    void sortJobs(QList<Job*> *JobsToSort, int MachineToCompare, int (Solver::*)(Job *, Job *, int));
};

#endif // SOLVER_H
