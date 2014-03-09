#include "headers\solution.h"

Solution::Solution()
{
    solutionIsOptimal = false;
    jobSetDominance = None;
    error = "Brak optymalnego rozwiązania";
}

Solution::Solution(QList<Job *> solution, Dominance setDominance)
{
    optimalOrder = solution;
    jobSetDominance = setDominance;

    solutionIsOptimal = true;
    error = "";
}

Solution::Solution(QList<Job*> solution)
{
    optimalOrder = solution;
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

QList<Job*> Solution::getOptimalOrder()
{
    return optimalOrder;
}

QString Solution::getOptimalOrderAsString()
{
    QString retString, tmp;

    for(int i=0; i < optimalOrder.length(); ++i)
    {
        tmp.setNum(optimalOrder[i]->getId());
        retString.append(tmp);
    }

    return retString;
}

Dominance Solution::getJobSetDominance()
{
    return jobSetDominance;
}

int Solution::getTimeCriteria()
{
    int ret = 1;
    int jobDuration = 0;
    int timeBeforeJobStart[3];

    for(int i=0; i<3; ++i)
        timeBeforeJobStart[i] = 0;

    for(int i=0; i<optimalOrder.length(); ++i)
    {
        jobDuration = optimalOrder[i]->getTimeFromMachinePlotting(1);

        if(timeBeforeJobStart[0] + jobDuration >= timeBeforeJobStart[1])
           timeBeforeJobStart[1] = timeBeforeJobStart[0] + jobDuration;

        timeBeforeJobStart[0] += jobDuration;

        jobDuration = optimalOrder[i]->getTimeFromMachinePlotting(2);
        if(timeBeforeJobStart[1] + jobDuration >= timeBeforeJobStart[2])
            timeBeforeJobStart[2] = timeBeforeJobStart[1] + jobDuration;

        timeBeforeJobStart[1] += jobDuration;

        jobDuration = optimalOrder[i]->getTimeFromMachinePlotting(3);
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
