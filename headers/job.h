#ifndef JOB_H
#define JOB_H

class Job
{
private:
    int id;
    int numberOfMashines;
    int * timesOnMashines;

public:
    Job(int Id, int NnumberOfMashines);
    ~Job();
    int getId();

    void setTimeOnMashine(int time, int mashine);
    int getTimeFromMashine(int mashine);
    int getTimeFromMashinePlotting(int mashine);

    bool TimeOnSecondMashineGreater();
};

#endif // JOB_H
