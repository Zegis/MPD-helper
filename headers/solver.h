#ifndef SOLVER_H
#define SOLVER_H

#include "job.h"
#include "dominance.h"
#include "solution.h"
#include "tree.h"
#include <QList>
#include <QVector>

class Solver
{    
public:
    Solver();

    virtual Solution Solve(QList<Job*> jobs, int MachineAmount);

    //Solution Johnson(QList<Job *> jobs, int MachineAmount);
    Solution Fifo(QList<Job *> jobs);
    Solution LPT(QList<Job *> jobs, int MachineAmount);
    Solution RPT(QList<Job *> jobs, int MachineAmount);
    Solution Hu(QList<Job *> jobs, int MachineAmount);

protected:

    //Dominance CheckDominance(QList<Job*> A);
    //bool JohnsonCondition(QList<Job*>A);

    void sortJobsDescendingBasedOnR(QList<Job*> *JobsToSort);

    int FindFreeMachine(int* MachineTimes, int MachineAmount);

    QVector< QList<Job*> > aproximateSequencing(QList<Job *> jobs, int MachineAmount);

    int AscendingBasedOnProcessingTime(Job *A, Job *B, int MachineToCompare);

    int DescendingBasedOnProcessingTime(Job* A, Job* B, int MachineToCompare);

    int AscendingBasedOnRelase(Job* A, Job* B, int def);

    void sortJobs(QList<Job*> *JobsToSort, int MachineToCompare, int (Solver::*)(Job *, Job *, int));

    Tree<int> createTree(QList<Job*> jobs);

    int findRoot(QList<Job*> jobs);

    void addNode(Tree<int>* workingTree, QList<Job*> jobs, int jobID);

    Job* getJobWithID(QList<Job*> jobs, int jobID);

    bool isValid(Job *JobToCheck , QVector< QList<Job *> > order, int machineNumber);

};

#endif // SOLVER_H
