#ifndef SOLUTION_H
#define SOLUTION_H

#include <QList>
#include <QString>
#include "job.h"
#include "dominance.h"

class Solution
{
public:
    Solution();
    Solution(QList<Job*> solution, Dominance setDominance);

    QList<Job*> getOptimalOrder();
    Dominance getJobSetDominance();

    QString getOptimalOrderAsString();

    bool isOptimal();

private:
    QList<Job*> optimalOrder;
    Dominance jobSetDominance;

    bool solutionIsOptimal;
};

#endif // SOLUTION_H
