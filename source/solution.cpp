#include "headers\solution.h"

Solution::Solution()
{
    solutionIsOptimal = false;
}

Solution::Solution(QList<Job *> solution, Dominance setDominance)
{
    optimalOrder = solution;
    jobSetDominance = setDominance;

    solutionIsOptimal = true;
}

QList<Job*> Solution::getOptimalOrder()
{
    return optimalOrder;
}

Dominance Solution::getJobSetDominance()
{
    return jobSetDominance;
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

bool Solution::isOptimal()
{
    return solutionIsOptimal;
}
