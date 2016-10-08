#ifndef MS_RCPSP_CROSSOVER_H
#define MS_RCPSP_CROSSOVER_H

/**
 * Abstract base class for crossover implementations.
 */
template <class T>
class Crossover {
 private:
  /** Crossover probability. */
  double p_cross;

 public:
  Crossover(double _p_cross) : p_cross(_p_cross) {}
  virtual ~Crossover() {}

  /**
   * Takes two specimen and performs crossover on them. Results in a new object.
   */
  virtual T *cross(T *a, T *b) = 0;

  /** Checks whether the crossover should take place. */
  bool should_cross();
};

#endif  // MS_RCPSP_CROSSOVER_H
