#ifndef MASHINE_H
#define MASHINE_H

#include<QList>
#include<QString>
#include"job.h"

enum Dominance
{
    None = 0,
    FirstOverSecond = 1,
    ThirdOverSecond = 2
};

class Mashine
{
private:

    int id;
    QList<Job*> jobs;

public:
    Mashine(int Id);
    Mashine(int Id, QList<Job*> Jobs);

    void SetJobs(QList<Job*> Jobs);

    void appendJob(Job * newJob);
    QString getOrder();

    int getEndingTimeForJob(int);

    int getJobId(int);

    int getJobDuration(int jobNumber);

    int getEndingTimeForLastJob();

    void clear();
};

#endif // MASHINE_H
