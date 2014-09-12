#ifndef RTPAPPROXIMATESOLVER_H
#define RTPAPPROXIMATESOLVER_H

#include "headers/approximateSolver.h"

class rtpApproximateSolver: public approximateSolver
{
    Solution Solve(QList<Job *> jobs, int MachineAmount);
};

#endif // RTPAPPROXIMATESOLVER_H
