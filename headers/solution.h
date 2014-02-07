#ifndef SOLUTION_H
#define SOLUTION_H

#include <QList>
#include "job.h"
#include "dominance.h"

class Solution
{
public:
    Solution();
    Solution(QList<Job*> solution, Dominance setDominance);

    QList<Job*> getOptimalOrder();
    Dominance getJobSetDominance();

private:
    QList<Job*> optimalOrder;
    Dominance jobSetDominance;
};

#endif // SOLUTION_H
