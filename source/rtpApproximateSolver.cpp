#include "headers/rtpApproximateSolver.h"

Solution rtpApproximateSolver::Solve(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job*> > orderedJobs = aproximateSequencing(jobs, MachineAmount);

    for(int i=0; i < orderedJobs.size(); ++i)
        sortJobs(&orderedJobs[i], 1, &rtpApproximateSolver::AscendingBasedOnProcessingTime);

    return Solution(orderedJobs);
}
