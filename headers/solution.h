#ifndef SOLUTION_H
#define SOLUTION_H

#include<QVector>
#include <QList>
#include <QString>
#include "job.h"
#include "dominance.h"

class Solution
{
public:
    Solution();
    Solution(QList<Job*> solution, Dominance setDominance);
    Solution(QList<Job *> solution, int NumberOfMachines, Dominance setDominance);
    Solution(QVector< QList<Job*> > solution);
    Solution(QList<Job*> solution);
    Solution(QString errorMsg);

    QList<Job*> getOptimalOrderForMachine(int MachineId);
    QString getOptimalOrderAsStringForMachine(int MachineId);

    Dominance getJobSetDominance();
    int getTimeCriteriaForMachine(int MachineId);

    bool isOptimal();
    QString getErrorMsg();

private:
    QVector< QList<Job*> > optimalOrder;
    Dominance jobSetDominance;
    QString error;

    bool solutionIsOptimal;
};

#endif // SOLUTION_H
