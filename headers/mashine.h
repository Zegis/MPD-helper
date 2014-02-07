#ifndef MASHINE_H
#define MASHINE_H

#include<QList>
#include<QString>
#include "headers/job.h"
#include "dominance.h"

class Mashine
{
private:

    int id;
    QList<Job*> jobs;

public:
    Mashine(int Id);
    Mashine(int Id, QList<Job*> Jobs);

    void setJobs(QList<Job*> Jobs);

    void appendJob(Job * newJob);

    int getEndingTimeForJob(int);

    int getJobId(int);

    int getJobDuration(int jobNumber);

    int getEndingTimeForLastJob();

    void clear();
};

#endif // MASHINE_H
