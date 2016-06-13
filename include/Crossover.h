//
// Created by ivan on 05.04.16.
//

#ifndef MS_RCPSP_CROSSOVER_H
#define MS_RCPSP_CROSSOVER_H


#include "Schedule.h"

/**
 * Base class for crossover implementations.
 */
class Crossover {
private:
    /**
     * Crossover probability.
     */
    double p_cross;
public:
    Crossover(double _p_cross) : p_cross(_p_cross) {}
    virtual ~Crossover() {}

    /**
     * Takes two specimen and perform crossover on them. Results in a new object.
     */
    virtual Schedule* cross(Schedule* a, Schedule* b) = 0;

    /**
     * Checks whether the crossover should take place, using the supplied probability.
     */
    bool should_cross();
};


#endif //MS_RCPSP_CROSSOVER_H
