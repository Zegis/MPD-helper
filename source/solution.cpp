#include "headers\solution.h"

Solution::Solution(QList<Job *> solution)
{
    optimalOrder = solution;
}

QList<Job*> Solution::getOptimalOrder()
{
    return optimalOrder;
}
