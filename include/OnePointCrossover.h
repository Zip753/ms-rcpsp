//
// Created by ivan on 26.04.16.
//

#ifndef MS_RCPSP_ONEPOINTCROSSOVER_H
#define MS_RCPSP_ONEPOINTCROSSOVER_H


#include "Crossover.h"

/**
 * Class that is used to perform one crossover of the specimen.
 */
class OnePointCrossover : public Crossover {
public:
    OnePointCrossover(double _p_cross) : Crossover(_p_cross) { }
    Schedule *cross(Schedule *a, Schedule *b);
};


#endif //MS_RCPSP_ONEPOINTCROSSOVER_H
