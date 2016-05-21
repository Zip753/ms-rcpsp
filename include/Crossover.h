//
// Created by ivan on 05.04.16.
//

#ifndef MS_RCPSP_CROSSOVER_H
#define MS_RCPSP_CROSSOVER_H


#include "Schedule.h"

class Crossover {
private:
    double p_cross;
public:
    Crossover(double _p_cross) : p_cross(_p_cross) {}
    virtual ~Crossover() {}
    virtual Schedule* cross(std::pair<Schedule*, Schedule*> p) = 0;
    bool should_cross();
};


#endif //MS_RCPSP_CROSSOVER_H
