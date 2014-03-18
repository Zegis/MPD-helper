#include "headers\solution.h"

Solution::Solution()
{
    solutionIsOptimal = false;
    jobSetDominance = None;
    error = "Brak optymalnego rozwiązania";
}

Solution::Solution(QList<Job *> solution, Dominance setDominance)
{
    optimalOrder.resize(3);
    optimalOrder[0] = solution;
    jobSetDominance = setDominance;

    solutionIsOptimal = true;
    error = "";
}

Solution::Solution(QList<Job *> solution, int NumberOfMachines, Dominance setDominance)
{
    optimalOrder.resize(NumberOfMachines);

    for(int i=0; i < NumberOfMachines; ++i)
        optimalOrder[i] = solution;

    jobSetDominance = setDominance;

    solutionIsOptimal = true;
    error = "";
}

Solution::Solution(QVector<QList<Job *> > solution)
{
    optimalOrder = solution;

    jobSetDominance = None;
    solutionIsOptimal = true;
    error = "";
}

Solution::Solution(QList<Job*> solution)
{
    optimalOrder.resize(1);
    optimalOrder[0] = solution;
    jobSetDominance = None;

    solutionIsOptimal = true;
    error = "";
}

Solution::Solution(QString errorMsg)
{
    solutionIsOptimal = false;
    error = errorMsg;
    jobSetDominance = None;
}

QList<Job*> Solution::getOptimalOrderForMachine(int MachineId)
{
    return optimalOrder[MachineId];
}

QString Solution::getOptimalOrderAsStringForMachine(int MachineId)
{
    QString retString, tmp;

    for(int i=0; i < optimalOrder[MachineId].length(); ++i)
    {
        tmp.setNum(optimalOrder[MachineId][i]->getId());
        retString.append(tmp);
    }

    return retString;
}

Dominance Solution::getJobSetDominance()
{
    return jobSetDominance;
}

int Solution::getTimeCriteriaForMachine(int MachineId)
{
    int ret = 1;
    int jobDuration = 0;
    int timeBeforeJobStart[3];

    for(int i=0; i<3; ++i)
        timeBeforeJobStart[i] = 0;

    for(int i=0; i<optimalOrder[MachineId].length(); ++i)
    {
        jobDuration = optimalOrder[MachineId][i]->getJobDuration(1);

        if(timeBeforeJobStart[0] + jobDuration >= timeBeforeJobStart[1])
           timeBeforeJobStart[1] = timeBeforeJobStart[0] + jobDuration;

        timeBeforeJobStart[0] += jobDuration;

        jobDuration = optimalOrder[MachineId][i]->getJobDuration(2);
        if(timeBeforeJobStart[1] + jobDuration >= timeBeforeJobStart[2])
            timeBeforeJobStart[2] = timeBeforeJobStart[1] + jobDuration;

        timeBeforeJobStart[1] += jobDuration;

        jobDuration = optimalOrder[MachineId][i]->getJobDuration(3);
        timeBeforeJobStart[2] += jobDuration;
    }

    ret = timeBeforeJobStart[2];

    return ret;
}


bool Solution::isOptimal()
{
    return solutionIsOptimal;
}

QString Solution::getErrorMsg()
{
    return error;
}
