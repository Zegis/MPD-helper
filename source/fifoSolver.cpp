#include "headers/fifoSolver.h"

fifoSolver::fifoSolver()
{
}

Solution fifoSolver::Solve(QList<Job *> jobs, int MachineAmount)
{
    sortJobs(&jobs,0,&fifoSolver::AscendingBasedOnRelase);

    return Solution(jobs);
}
