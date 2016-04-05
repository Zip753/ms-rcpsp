#ifndef MUTATOR_H
#define MUTATOR_H

#include "Schedule.h"

class Mutator {
public:
    Mutator(double _p_mut) : p_mut(_p_mut) {};
    // create new sample that is a probable mutation of given one
    Schedule* mutate(Schedule* sample);
    // mutate given sample without creating a new one
    Schedule* force_mutate(Schedule *sample);
private:
    double p_mut;
};

#endif // MUTATOR_H
