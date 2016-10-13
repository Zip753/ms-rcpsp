#ifndef MS_RCPSP_RANDOM_H
#define MS_RCPSP_RANDOM_H

#include <random>

namespace Util {

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
  static std::random_device rd;
  static std::mt19937 gen;
  static std::uniform_int_distribution<> rand_int;
  static std::uniform_real_distribution<> rand_real;
};

};  // namespace Util

#endif  // MS_RCPSP_RANDOM_H
