#ifndef SOLUTION_H
#define SOLUTION_H

#include <QList>
#include "job.h"
#include "dominance.h"

class Solution
{
public:
    Solution(QList<Job*> solution);

    QList<Job*> getOptimalOrder();

private:
    QList<Job*> optimalOrder;
    Dominance jobSetDominance;
};

#endif // SOLUTION_H
