#ifndef CROSSOVER_H
#define CROSSOVER_H

#include <utility>
#include "Schedule.h"

class Crossover {
public:
    Crossover(double _p_cross) : p_cross(_p_cross) {};
    Schedule* cross(std::pair<Schedule*, Schedule*> p);
    bool should_cross();
private:
    double p_cross;
};

#endif // CROSSOVER_H
