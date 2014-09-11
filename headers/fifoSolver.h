#ifndef FIFOSOLVER_H
#define FIFOSOLVER_H

#include "headers/solver.h"

class fifoSolver: public Solver
{
   public:
      fifoSolver();
      Solution Solve(QList<Job*> jobs, int MachineAmount);
};

#endif // FIFOSOLVER_H
