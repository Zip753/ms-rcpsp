#ifndef POPULATION_H
#define POPULATION_H

#include "Schedule.h"

class Selector;

/**
 * Class that represents the Population, i.e. the list of Schedule-specimen.
 */
class Population {
public:
    /**
     * Creates the population from the list of scecimen.
     * @param size size of population.
     * @param sln list of specimen.
     */
    Population(int size, Schedule** sln) : genotype(sln), n(size) {};

    /**
     * Creates the population of the given size with random specimen.
     * @param size size of population.
     */
    Population(int size);
    ~Population();

    /**
     * Size of the population.
     */
    int size();

    /**
     * Specimen with the least fitness function in the population.
     */
    Schedule* best();

    /**
     * List of specimen.
     */
    Schedule **genotype;

    /**
     * Show statistical information of the population: best, average and worst specimen.
     * @param stream output stream where the information is written.
     */
    void showStat(FILE *stream);
private:
    /**
     * Size of the population.
     */
    int n;
};

#endif // POPULATION_H
