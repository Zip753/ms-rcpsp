//
// Created by ivan on 26.04.16.
//

#ifndef MS_RCPSP_ONEPOINTCROSSOVER_H
#define MS_RCPSP_ONEPOINTCROSSOVER_H


#include "Crossover.h"

class OnePointCrossover : public Crossover {
public:
    OnePointCrossover(double _p_cross) : Crossover(_p_cross) { }
    Schedule *cross(std::pair<Schedule *, Schedule *> p);
};


#endif //MS_RCPSP_ONEPOINTCROSSOVER_H
