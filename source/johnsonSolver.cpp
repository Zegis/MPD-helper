#include "headers/johnsonSolver.h"

johnsonSolver::johnsonSolver()
{
}

Solution johnsonSolver::Solve(QList<Job *> jobs, int MachineAmount)
{
    QList<Job*> B;

    int JobCount = jobs.length();
    Dominance dominance = None;

    if(MachineAmount == 3)
        dominance = CheckDominance(jobs);

    if(MachineAmount != 3 || dominance != None)
    {
        for(int i=0; i<JobCount;)
        {
            if(jobs[i]->getTimeFromMachine(1) > jobs[i]->getTimeFromMachine(2))
            {
                Job* tmp = jobs[i];

                B.append(tmp);
                jobs.removeAt(i);
                --JobCount;
            }
            else
                ++i;
        }

        if(jobs.size() > 0) sortJobs(&jobs,1,&johnsonSolver::AscendingBasedOnProcessingTime);
        if(B.size() > 0) sortJobs(&B,2,&johnsonSolver::DescendingBasedOnProcessingTime);

        if(JohnsonCondition(jobs+B))
            return Solution(jobs+B, MachineAmount, dominance);
        else
            return Solution("Brak optymalnego rozwiązania");
    }
    return Solution("Brak dominacji nad 2 maszyną");
}

bool johnsonSolver::JohnsonCondition(QList<Job *> A)
{
    int cmp1, cmp2;
    int JobCount = A.length();
    for(int i=0; i < JobCount-1; ++i)
    {

        cmp1 = ( A[i]->getTimeFromMachine(1) < A[i+1]->getTimeFromMachine(2) ) ?
                    A[i]->getTimeFromMachine(1) : A[i+1]->getTimeFromMachine(2);

        cmp2 = (A[i+1]->getTimeFromMachine(1)) < A[i]->getTimeFromMachine(2) ?
                    A[i+1]->getTimeFromMachine(1) : A[i]->getTimeFromMachine(2) ;

        if(cmp1 > cmp2)
            return false;
    }

    return true;
}

Dominance johnsonSolver::CheckDominance(QList<Job *> A)
{
    Dominance ret = None;

    int maxP2 = A[0]->getTimeFromMachinePlotting(2);
    int minP1 = A[0]->getTimeFromMachinePlotting(1);
    int minP3 = A[0]->getTimeFromMachinePlotting(3);;


    int JobCount = A.length();

    for(int i=1; i<JobCount; ++i)
    {
        if (A[i]->getTimeFromMachinePlotting(2) > maxP2) maxP2 = A[i]->getTimeFromMachinePlotting(2);
        if (A[i]->getTimeFromMachinePlotting(1) < minP1) minP1 = A[i]->getTimeFromMachinePlotting(1);
        if (A[i]->getTimeFromMachinePlotting(3) < minP3) minP3 = A[i]->getTimeFromMachinePlotting(3);
    }

    if(minP1 >= maxP2)
        ret = FirstOverSecond;
    else if (minP3 >= maxP2)
        ret = ThirdOverSecond;
    else
        ret = None;

    return ret;
}
