#ifndef JOHNSONSOLVER_H
#define JOHNSONSOLVER_H

#include "headers/solver.h"

class johnsonSolver: public Solver
{
    public:
        johnsonSolver();
        Solution Solve(QList<Job*> jobs, int MachineAmount);

    private:

        Dominance CheckDominance(QList<Job*> A);
        bool JohnsonCondition(QList<Job*>A);
};

#endif // JOHNSONSOLVER_H
