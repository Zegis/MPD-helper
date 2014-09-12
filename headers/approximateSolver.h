#ifndef APPROXIMATESOLVER_H
#define APPROXIMATESOLVER_H

#include "headers/solver.h"

class approximateSolver: public Solver
{
public:
    virtual Solution Solve(QList<Job *> jobs, int MachineAmount) = 0;

protected:

    int FindFreeMachine(int* MachineTimes, int MachineAmount);

    QVector< QList<Job*> > aproximateSequencing(QList<Job *> jobs, int MachineAmount);
};

#endif // APPROXIMATESOLVER_H
