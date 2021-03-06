#ifndef JOB_H
#define JOB_H

class Job
{
private:
    int id;
    int numberOfMachines;
    int * timesOnMachines;

    int preludingJobs[3];

    int r;

public:
    Job(int Id, int NumberOfMachines);

    static Job* createEmptyJob();

    ~Job();
    int getId();

    void setTimeOnMachine(int time, int machine);
    int getTimeFromMachine(int machine);
    int getTimeFromMachinePlotting(int machine);
    int getJobDuration(int machine);

    bool TimeOnSecondMachineGreater();

    void setRelaseTime(int relase);
    int getRelaseTime();

    bool preludes(int id);

    void addProceedingJob(int id);

    int* getPreludingJobs();
};

#endif // JOB_H
