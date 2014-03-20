#ifndef SOLVER_H
#define SOLVER_H

#include "job.h"
#include "dominance.h"
#include "solution.h"
#include <QList>
#include <QVector>

class Solver
{    
public:
    Solver();
    Solution Johnson(QList<Job *> jobs, int MachineAmount);
    Solution Fifo(QList<Job *> jobs);
    Solution LPT(QList<Job *> jobs, int MachineAmount);
    Solution RPT(QList<Job *> jobs, int MachineAmount);

private:
    void sortJobsAccordingToMachine(QList<Job*> *JobsToSort, int machineId, int option);
    Dominance CheckDominance(QList<Job*> A);
    bool JohnsonCondition(QList<Job*>A);

    void sortJobsDescendingBasedOnR(QList<Job*> *JobsToSort);

    int FindFreeMachine(int* MachineTimes, int MachineAmount);

    void sortJobsAscendingBasedOnP(QList<Job*> *JobsToSort);
    void sortJobsDescendingBasedOnP(QList<Job*> *JobsToSort);

    QVector< QList<Job*> > aproximateSequencing(QList<Job *> jobs, int MachineAmount);

};

#endif // SOLVER_H
