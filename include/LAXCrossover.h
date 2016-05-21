#ifndef CROSSOVER_H
#define CROSSOVER_H

#include <utility>
#include "Schedule.h"
#include "Crossover.h"

class LAXCrossover : public Crossover {
public:
    LAXCrossover(double _p_cross) : Crossover(_p_cross) { }
    Schedule* cross(std::pair<Schedule*, Schedule*> p);
};

#endif // CROSSOVER_H
