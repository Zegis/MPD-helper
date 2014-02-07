#include "headers\solution.h"

Solution::Solution()
{
}

Solution::Solution(QList<Job *> solution, Dominance setDominance)
{
    optimalOrder = solution;
    jobSetDominance = setDominance;
}

QList<Job*> Solution::getOptimalOrder()
{
    return optimalOrder;
}

Dominance Solution::getJobSetDominance()
{
    return jobSetDominance;
}
