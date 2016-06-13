#ifndef MUTATOR_H
#define MUTATOR_H

#include "Schedule.h"

/**
 * Class used to perform mutation on the specimen.
 */
class Mutator {
public:
    /**
     * Create Mutator instance with given mutation probability.
     * @param _p_mut mutation probability.
     */
    Mutator(double _p_mut) : p_mut(_p_mut) {};

    /**
     * Perform mutation on the given sample.
     * Returns new instance of Schedule.
     */
    Schedule* mutate(Schedule* sample);

    /**
     * Mutate given sample without creating a new one.
     * Used to force mutation in the specimen in order to remove clones from the population.
     */
    void force_mutate(Schedule *sample);
private:
    /**
     * Mutation probability.
     */
    double p_mut;

    /**
     * Mutate single gene in the specimen.
     * @param sample specimen to operate on.
     * @param idx index of the gene to be mutated.
     */
    void mutate_gene(Schedule *sample, int idx);
};

#endif // MUTATOR_H
