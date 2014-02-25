#ifndef SOLVER_H
#define SOLVER_H

#include "job.h"
#include "dominance.h"
#include "solution.h"
#include <QList>

class Solver
{    
public:
    Solver();
    Solution Johnson(QList<Job *> jobs, int MashineAmount);
    Solution Fifo(QList<Job *> jobs);

private:
    void sortJobsAccordingToMashine(QList<Job*> *JobsToSort, int mashineId, int option);
    Dominance CheckDominance(QList<Job*> A);
    bool JohnsonCondition(QList<Job*>A);
    void sortJobsDescendingBasedOnR(QList<Job*> *JobsToSort);

};

#endif // SOLVER_H
