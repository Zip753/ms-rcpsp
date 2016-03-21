#ifndef MUTATOR_H
#define MUTATOR_H

#include "Schedule.h"

class Mutator {
public:
    Mutator(double _p_mut) : p_mut(_p_mut) {};
    Schedule* mutate(Schedule* sample);
private:
    double p_mut;
};

#endif // MUTATOR_H
