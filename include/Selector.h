#ifndef SELECTOR_H
#define SELECTOR_H

#include "Schedule.h"
#include "Population.h"

class Population;
class Selector {
public:
    Selector(int _n = 5) : n(_n) {};
    Schedule* select(Population* p);
private:
    int n;
};

#endif // SELECTOR_H
