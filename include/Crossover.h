#ifndef CROSSOVER_H
#define CROSSOVER_H

#include <utility>
#include "Schedule.h"

class Crossover {
public:
    Crossover(double _p_cross) : p_cross(_p_cross) {};
    std::pair<Schedule*, Schedule*> cross(std::pair<Schedule*, Schedule*> p);
private:
    double p_cross;
};

#endif // CROSSOVER_H
