#ifndef JOB_H
#define JOB_H

class Job
{
private:
    int id;
    int numberOfMachines;
    int * timesOnMachines;

    int r;

public:
    Job(int Id, int NumberOfMachines);
    ~Job();
    int getId();

    void setTimeOnMachine(int time, int machine);
    int getTimeFromMachine(int machine);
    int getTimeFromMachinePlotting(int machine);
    int getJobDuration(int machine);

    bool TimeOnSecondMachineGreater();

    void setRelaseTime(int relase);
    int getRelaseTime();
};

#endif // JOB_H
