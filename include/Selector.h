#ifndef SELECTOR_H
#define SELECTOR_H

#include "Schedule.h"
#include "Population.h"

class Population;

/**
 * Class used to select candidate specimen to the next population from the current one.
 * Implemented as tournament selector.
 */
class Selector {
public:
    /**
     * Creates Selector instance with given tournament size.
     * @param _n tournament size, defaults to 5.
     */
    Selector(int _n = 5) : n(_n) {};

    /**
     * Select the candidate specimen from the given population.
     * @param p population to select the specimen from.
     */
    Schedule* select(Population* p);
private:
    /**
     * Size of the tournament.
     */
    int n;
};

#endif // SELECTOR_H
