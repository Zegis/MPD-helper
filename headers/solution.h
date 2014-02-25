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
    Solution(QList<Job*> solution);
    Solution(QString errorMsg);

    QList<Job*> getOptimalOrder();
    QString getOptimalOrderAsString();

    Dominance getJobSetDominance();
    int getTimeCriteria();

    bool isOptimal();
    QString getErrorMsg();

private:
    QList<Job*> optimalOrder;
    Dominance jobSetDominance;
    QString error;

    bool solutionIsOptimal;
};

#endif // SOLUTION_H
