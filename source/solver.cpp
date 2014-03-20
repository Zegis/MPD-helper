#include "headers/solver.h"

Solver::Solver()
{
}

Solution Solver::Johnson(QList<Job*> jobs, int MachineAmount)
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

        if(jobs.size() > 0) sortJobsAccordingToMachine(&jobs,1,1);
        if(B.size() > 0) sortJobsAccordingToMachine(&B,2,0);

        if(JohnsonCondition(jobs+B))
            return Solution(jobs+B, MachineAmount, dominance);
        else
            return Solution("Brak optymalnego rozwiązania");
    }
    return Solution("Brak dominacji nad 2 maszyną");
}

bool Solver::JohnsonCondition(QList<Job *> A)
{
    int cmp1, cmp2;
    int JobCount = A.length();
    for(int i=0; i < JobCount-1; ++i)
    {
        cmp1 = ( A[i]->getTimeFromMachinePlotting(1) < A[i+1]->getTimeFromMachinePlotting(2) ) ? A[i]->getTimeFromMachinePlotting(1) : A[i+1]->getTimeFromMachinePlotting(2);

        cmp2 = (A[i+1]->getTimeFromMachinePlotting(1)) < A[i]->getTimeFromMachinePlotting(2) ? A[i+1]->getTimeFromMachinePlotting(1) : A[i]->getTimeFromMachinePlotting(2) ;

        if(cmp1 > cmp2)
            return false;
    }

    return true;
}

Dominance Solver::CheckDominance(QList<Job *> A)
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

void Solver::sortJobsAccordingToMachine(QList<Job*>* jobs, int mashineId, int option)
{
    if(option == 1) // nonRising
    {
        for(int i=0; i < jobs->size(); ++i)
            for(int j=0; j < jobs->size() - 1 - i; ++j)
            {
                if((*jobs)[j]->getTimeFromMachine(mashineId) > (*jobs)[j+1]->getTimeFromMachine(mashineId))
                    jobs->swap(j,j+1);
            }
    }
    else if (option == 0) // nonDecreasing
    {
        for(int i=0; i < jobs->size(); ++i)
            for(int j=0; j < jobs->size() - 1 - i; ++j)
            {
                if((*jobs)[j]->getTimeFromMachine(mashineId) < (*jobs)[j+1]->getTimeFromMachine(mashineId))
                    jobs->swap(j,j+1);
            }
    }
}

Solution Solver::Fifo(QList<Job *> jobs)
{
    sortJobsDescendingBasedOnR(&jobs);

    return Solution(jobs);
}

void Solver::sortJobsDescendingBasedOnR(QList<Job *> *JobsToSort)
{
    int n = JobsToSort->size();
    do
    {
        for(int i=0; i < n -1; ++i)
            if( (*JobsToSort)[i]->getRelaseTime() > (*JobsToSort)[i+1]->getRelaseTime())
                JobsToSort->swap(i, i+1);

        --n;
    }while(n > 1);
}

Solution Solver::LPT(QList<Job *> jobs, int MachineAmount)
{
    return Solution(aproximateSequencing(jobs,MachineAmount));
}

QVector< QList<Job*> > Solver::aproximateSequencing(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job*> > orderedJobs(MachineAmount);
    int* freeTimeOnMachine = new int[MachineAmount];

    int MachineToAssignJob = 0;

    for(int i=0; i<MachineAmount; ++i)
        freeTimeOnMachine[i] = 0;

    sortJobs(&jobs, &Solver::AscendingBasedOnProcessingTime);

    for(int i=0; i < jobs.length(); ++i)
    {
        MachineToAssignJob = FindFreeMachine(freeTimeOnMachine, MachineAmount);

        orderedJobs[MachineToAssignJob].append(jobs[i]);

        freeTimeOnMachine[MachineToAssignJob] += jobs[i]->getTimeFromMachinePlotting(1);
    }

    delete[] freeTimeOnMachine;

    return orderedJobs;
}

Solution Solver::RPT(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job*> > orderedJobs = aproximateSequencing(jobs, MachineAmount);

    for(int i=0; i < orderedJobs.size(); ++i)
        sortJobsDescendingBasedOnP(&orderedJobs[i]);

    return Solution(orderedJobs);
}

void Solver::sortJobsDescendingBasedOnP(QList<Job *> *JobsToSort)
{
    int n = JobsToSort->size();
    do
    {
        for(int i=0; i < n-1; ++i)
            if( (*JobsToSort)[i]->getTimeFromMachinePlotting(1) > (*JobsToSort)[i+1]->getTimeFromMachinePlotting(1) )
                JobsToSort->swap(i, i+1);
        --n;
    }while(n>1);
}

int Solver::FindFreeMachine(int* MachineTimes, int MachineAmount)
{
    if(MachineAmount == 1)
        return 0;
    else
    {
        int ret = 0;
        for(int i=1; i < MachineAmount; ++i)
        {
            if( MachineTimes[i] < MachineTimes[ret])
                ret = i;
        }
        return ret;
    }
}

void Solver::sortJobs(QList<Job *> *JobsToSort, int (Solver::* comparator)(Job *, Job *))
{
    int n = JobsToSort->size();
    do
    {
        for(int i=0; i > n-1; ++i)
        {
            if( (this->*comparator)( (*JobsToSort)[i], (*JobsToSort)[i+1]) == 1)
                    JobsToSort->swap(i,i+1);
        }
        --n;
    }while(n > 1);
}

int Solver::AscendingBasedOnProcessingTime(Job* A, Job* B)
{
    if( A->getTimeFromMachinePlotting(1) < B->getTimeFromMachinePlotting(1) )
        return 1;
    else
        return 0;
}
