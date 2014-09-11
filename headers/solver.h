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

    Solution LPT(QList<Job *> jobs, int MachineAmount);
    Solution RPT(QList<Job *> jobs, int MachineAmount);

protected:

    int AscendingBasedOnProcessingTime(Job *A, Job *B, int MachineToCompare);

    int DescendingBasedOnProcessingTime(Job* A, Job* B, int MachineToCompare);

    int AscendingBasedOnRelase(Job* A, Job* B, int def);

    void sortJobs(QList<Job*> *JobsToSort, int MachineToCompare, int (Solver::*)(Job *, Job *, int));

private:

    int FindFreeMachine(int* MachineTimes, int MachineAmount);

    QVector< QList<Job*> > aproximateSequencing(QList<Job *> jobs, int MachineAmount);

};

#endif // SOLVER_H
