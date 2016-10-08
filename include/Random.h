#ifndef MS_RCPSP_RANDOM_H
#define MS_RCPSP_RANDOM_H

/** @brief Helper class used to generate random values. */
class Random {
 public:
  /** Generates random integer number. */
  static int randint();

  /**
   * Checks whether the randomly generated number satisfied the given
   * probability.
   * @param prob Probability value from 0 to 1.
   */
  static bool rand(double prob);

 private:
  /** Seed random values. Makes sure that values are only seeded once. */
  static void seed();

  /** Cache variable to check whether the seed has already been initiated. */
  static bool _seed;
};

#endif  // MS_RCPSP_RANDOM_H
