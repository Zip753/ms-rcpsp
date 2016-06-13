//
// Created by ivan on 24.04.16.
//

#ifndef MS_RCPSP_UNIFORMCROSSOVER_H
#define MS_RCPSP_UNIFORMCROSSOVER_H


#include "Crossover.h"

/**
 * Class that is used to perform uniform crossover of the specimen.
 */
class UniformCrossover : public Crossover {
public:
    UniformCrossover(double _p_cross) : Crossover(_p_cross) { }
    Schedule *cross(Schedule *a, Schedule *b);
};


#endif //MS_RCPSP_UNIFORMCROSSOVER_H
