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

        if(jobs.size() > 0) sortJobs(&jobs,1,&Solver::AscendingBasedOnProcessingTime);
        if(B.size() > 0) sortJobs(&B,2,&Solver::DescendingBasedOnProcessingTime);

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

Solution Solver::Fifo(QList<Job *> jobs)
{
    sortJobs(&jobs,0,&Solver::AscendingBasedOnRelase);

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

    sortJobs(&jobs,1, &Solver::DescendingBasedOnProcessingTime);

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
        sortJobs(&orderedJobs[i], 1, &Solver::AscendingBasedOnProcessingTime);

    return Solution(orderedJobs);
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

void Solver::sortJobs(QList<Job *> *JobsToSort, int MachineToCompare, int (Solver::* comparator)(Job *, Job *, int))
{
    int n = JobsToSort->size();
    do
    {
        for(int i=0; i < n-1; ++i)
        {
            if( (this->*comparator)( (*JobsToSort)[i], (*JobsToSort)[i+1], MachineToCompare) == 1)
                    JobsToSort->swap(i,i+1);
        }
        --n;
    }while(n > 1);
}

int Solver::AscendingBasedOnProcessingTime(Job* A, Job* B, int MachineToCompare)
{
    if( A->getTimeFromMachinePlotting(MachineToCompare) > B->getTimeFromMachinePlotting(MachineToCompare) )
        return 1;
    else
        return 0;
}

int Solver::DescendingBasedOnProcessingTime(Job *A, Job *B, int MachineToCompare)
{
    if( A->getTimeFromMachinePlotting(MachineToCompare) < B->getTimeFromMachinePlotting(MachineToCompare) )
        return 1;
    else
        return 0;
}

int Solver::AscendingBasedOnRelase(Job* A, Job* B, int def = 0)
{
    if( A->getRelaseTime() > B->getRelaseTime())
        return 1;
    else
        return 0;
}

Solution Solver::Hu(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job *> > orderedJobs(MachineAmount);

    Tree<int> inTree = createTree(jobs);

    QVector< QList<int> > leveledJobs = inTree.getNodeLevels();
    QVector< QList<int> >::Iterator elementRemover;

    int jobID;
    int counter = 0;
    while(leveledJobs.size() != 0)
    {

        int MachineToFill;
        while(leveledJobs.last().size() != 0)
        {

            Job* jobToAdd = 0;
            MachineToFill = counter % MachineAmount;

            // Check proceedings
            // If there's no proceeding job at this time add like this:
            for(int i=0; i < leveledJobs.last().size(); ++i)
            {
                jobToAdd = getJobWithID(jobs, (leveledJobs.last())[i]);
                if(isValid(jobToAdd, orderedJobs, MachineToFill))
                {
                    leveledJobs.last().takeAt(i);
                    break;
                }
                else
                {
                    jobToAdd = 0;
                }
            }

            if( jobToAdd == 0)
                jobToAdd = createEmptyJob();

            orderedJobs[MachineToFill].append(jobToAdd);

            ++counter;
        }

        elementRemover = leveledJobs.end();
        --elementRemover;

        leveledJobs.erase(elementRemover);
    }

    return Solution(orderedJobs);
}


Tree<int> Solver::createTree(QList<Job*> jobs)
{
    Tree<int> ret;

    int rootID = findRoot(jobs);

    ret.insertRoot(&rootID);
    addNode(&ret, jobs, rootID);

    return ret;
}

int Solver::findRoot(QList<Job*> jobs)
{
    int rootId = 0;
    bool found = false;

    while(jobs.size() != 0 && !found)
    {
        rootId = jobs.takeFirst()->getId();
        for(int i=0; i < jobs.length(); ++i)
        {
            if(jobs[i]->proceeds(rootId))
                break;
            else if(i == jobs.length()-1)
                found = true;
        }
    }

    return rootId;
}

void Solver::addNode(Tree<int>* workingTree, QList<Job*> jobs, int jobID)
{
    int offsetForList = -1;

    int* proceedingJobs = jobs[jobID+offsetForList]->getProceedingJobs();
    for(int i=0; i<3; ++i)
    {
        if(proceedingJobs[i] != 0)
        {
            workingTree->insertJob(&(proceedingJobs[i]),jobID);
            addNode(workingTree, jobs, proceedingJobs[i]);
        }
    }
}

Job* Solver::getJobWithID(QList<Job*> jobs, int jobID)
 {
     for(int i=0; i < jobs.size(); ++i)
     {
         if(jobs.at(i)->getId() == jobID)
             return jobs.takeAt(i);
     }
 }

Job* Solver::createEmptyJob()
{
    Job* ret = new Job(0,1);
    ret->setTimeOnMachine(1,1);

    return ret;
}

bool Solver::isValid(Job* JobToCheck, QVector<QList<Job *> > order, int machineNumber)
{
    // Check if order contains JobToCeck's proceeding jobs in this time
    // use JobToCheck->proceeds(int id)

    if(machineNumber == 0)
        return true;

    for(int i=0; i < machineNumber; ++i)
        if (JobToCheck->proceeds(order[i].last()->getId()))
            return false;


    return true;
}
