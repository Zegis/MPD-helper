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

QString Solution::getErrorMsg()
{
    return error;
}
