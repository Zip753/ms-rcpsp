#ifndef RANDOM_H
#define RANDOM_H

/**
 * Helper class used to generate random values.
 */
class Random {
public:
    /**
     * Generates random integer number.
     */
    static int randint();

    /**
     * Checks whether the randomly generated number satisfied the given probability.
     * @param prob probability value from 0 to 1
     */
    static bool rand(double prob);
private:
    /**
     * Seed random values.
     * Uses _seed variable to check whether the seed has already been initiated.
     */
    static void seed();

    /**
     * Cache variable to check whether the seed has already been initiated.
     */
    static bool _seed;
};

#endif // RANDOM_H
