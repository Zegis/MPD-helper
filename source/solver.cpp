#include "headers/solver.h"

Solver::Solver()
{
}

QList<Job*> Solver::Johnson(QList<Job*> jobs, int MashineAmount)
{
    QList<Job*> B;

    int JobCount = jobs.length();
    Dominance dominance = None;

    if(MashineAmount == 3)
        dominance = CheckDominance(jobs);

    if(MashineAmount != 3 || dominance != None)
    {
        for(int i=0; i<JobCount;)
        {
            if(jobs[i]->getTimeFromMashine(1) > jobs[i]->getTimeFromMashine(2))
            {
                Job* tmp = jobs[i];

                B.append(tmp);
                jobs.removeAt(i);
                --JobCount;
            }
            else
                ++i;
        }

        if(jobs.size() > 0) sortJobsAccordingToMashine(&jobs,1,1);
        if(B.size() > 0) sortJobsAccordingToMashine(&B,2,0);

        return (jobs+B);
    }
    return B;
}

bool Solver::JohnsonCondition(QList<Job *> A)
{
    int cmp1, cmp2;
    int JobCount = A.length();
    for(int i=0; i < JobCount-1; ++i)
    {
       // cmp1 = (first->getJobDuration(i) < second->getJobDuration(i+1)) ? first->getJobDuration(i) : second->getJobDuration(i+1);

      //  cmp2 = (first->getJobDuration(i+1) < second->getJobDuration(i)) ? first->getJobDuration(i+1) : second->getJobDuration(i);

        if(cmp1 > cmp2)
            return false;
    }

    return true;
}

Dominance Solver::CheckDominance(QList<Job *> A)
{
    Dominance ret = None;

    int maxP2 = A[0]->getTimeFromMashinePlotting(2);
    int minP1 = A[0]->getTimeFromMashinePlotting(1);
    int minP3 = A[0]->getTimeFromMashinePlotting(3);;


    int JobCount = A.length();

    for(int i=1; i<JobCount; ++i)
    {
        if (A[i]->getTimeFromMashinePlotting(2) > maxP2) maxP2 = A[i]->getTimeFromMashinePlotting(2);
        if (A[i]->getTimeFromMashinePlotting(1) < minP1) minP1 = A[i]->getTimeFromMashinePlotting(1);
        if (A[i]->getTimeFromMashinePlotting(3) < minP3) minP3 = A[i]->getTimeFromMashinePlotting(3);
    }

    if(minP1 >= maxP2)
        ret = FirstOverSecond;
    else if (minP3 >= maxP2)
        ret = ThirdOverSecond;
    else
        ret = None;

    return ret;
}

void Solver::sortJobsAccordingToMashine(QList<Job*>* jobs, int mashineId, int option)
{
    if(option == 1) // nonRising
    {
        for(int i=0; i < jobs->size(); ++i)
            for(int j=0; j < jobs->size() - 1 - i; ++j)
            {
                if((*jobs)[j]->getTimeFromMashine(mashineId) > (*jobs)[j+1]->getTimeFromMashine(mashineId))
                    jobs->swap(j,j+1);
            }
    }
    else if (option == 0) // nonDecreasing
    {
        for(int i=0; i < jobs->size(); ++i)
            for(int j=0; j < jobs->size() - 1 - i; ++j)
            {
                if((*jobs)[j]->getTimeFromMashine(mashineId) < (*jobs)[j+1]->getTimeFromMashine(mashineId))
                    jobs->swap(j,j+1);
            }
    }
}