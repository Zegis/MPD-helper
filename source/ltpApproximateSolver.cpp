#include "headers/ltpApproximateSolver.h"

Solution ltpApproximateSolver::Solve(QList<Job *> jobs, int MachineAmount)
{
    return Solution(aproximateSequencing(jobs,MachineAmount));
}
