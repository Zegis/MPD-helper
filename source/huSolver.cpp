#include "headers/huSolver.h"

huSolver::huSolver()
{
}

Solution huSolver::Solve(QList<Job *> jobs, int MachineAmount)
{
    QVector< QList<Job *> > orderedJobs(MachineAmount);

    Tree<int> inTree = createTree(jobs);

    QVector< QList<int> > leveledJobs = inTree.getNodeLevels();
    QVector< QList<int> >::Iterator elementRemover;

    int counter = 0;
    while(leveledJobs.size() != 0)
    {

        int MachineToFill;
        while(leveledJobs.last().size() != 0)
        {

            Job* jobToAdd = 0;
            MachineToFill = counter % MachineAmount;

            // Check preludings
            // If there's no preluding job at this time add like this:
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
                jobToAdd = Job::createEmptyJob();

            orderedJobs[MachineToFill].append(jobToAdd);

            ++counter;
        }

        elementRemover = leveledJobs.end();
        --elementRemover;

        leveledJobs.erase(elementRemover);
    }

    return Solution(orderedJobs);
}

Tree<int> huSolver::createTree(QList<Job*> jobs)
{
    Tree<int> ret;

    int rootID = findRoot(jobs);

    ret.insertRoot(&rootID);
    addNode(&ret, jobs, rootID);

    return ret;
}

int huSolver::findRoot(QList<Job*> jobs)
{
    int rootId = 0;
    bool found = false;

    while(jobs.size() != 0 && !found)
    {
        rootId = jobs.takeFirst()->getId();
        for(int i=0; i < jobs.length(); ++i)
        {
            if(jobs[i]->preludes(rootId))
                break;
            else if(i == jobs.length()-1)
                found = true;
        }
    }

    return rootId;
}

void huSolver::addNode(Tree<int>* workingTree, QList<Job*> jobs, int jobID)
{
    int offsetForList = -1;

    int* preludingJobs = jobs[jobID+offsetForList]->getPreludingJobs();
    for(int i=0; i<3; ++i)
    {
        if(preludingJobs[i] != 0)
        {
            workingTree->insertJob(&(preludingJobs[i]),jobID);
            addNode(workingTree, jobs, preludingJobs[i]);
        }
    }
}

Job* huSolver::getJobWithID(QList<Job*> jobs, int jobID)
{
     for(int i=0; i < jobs.size(); ++i)
     {
         if(jobs.at(i)->getId() == jobID)
             return jobs.takeAt(i);
     }

     return Job::createEmptyJob();
}


bool huSolver::isValid(Job* JobToCheck, QVector<QList<Job *> > order, int machineNumber)
{
    // Check if order contains JobToCeck's proceeding jobs in this time
    // use JobToCheck->proceeds(int id)

    if(machineNumber == 0)
        return true;

    for(int i=0; i < machineNumber; ++i)
        if (JobToCheck->preludes(order[i].last()->getId()))
            return false;


    return true;
}
