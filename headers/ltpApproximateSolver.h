#ifndef LTPAPPROXIMATESOLVER_H
#define LTPAPPROXIMATESOLVER_H

#include "headers/approximateSolver.h"

class ltpApproximateSolver: public approximateSolver
{
    Solution Solve(QList<Job *> jobs, int MachineAmount);
};

#endif // LTPAPPROXIMATESOLVER_H
