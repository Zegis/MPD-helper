#ifndef HUSOLVER_H
#define HUSOLVER_H

#include "headers/solver.h"
#include "tree.h"

class huSolver: public Solver
{
public:
    huSolver();
    Solution Solve(QList<Job *> jobs, int MachineAmount);

private:
    Tree<int> createTree(QList<Job*> jobs);

    void addNode(Tree<int>* workingTree, QList<Job*> jobs, int jobID);

    Job* getJobWithID(QList<Job*> jobs, int jobID);

    bool isValid(Job *JobToCheck , QVector< QList<Job *> > order, int machineNumber);

    int findRoot(QList<Job*> jobs);
};

#endif // HUSOLVER_H
