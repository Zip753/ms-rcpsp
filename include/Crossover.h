#ifndef MS_RCPSP_CROSSOVER_H
#define MS_RCPSP_CROSSOVER_H

template <class T>
class Crossover {
 private:
  double p_cross;

 public:
  Crossover(double _p_cross) : p_cross(_p_cross) {}
  virtual ~Crossover() {}
  virtual T *cross(T *a, T *b) = 0;
  bool should_cross();
};

#endif  // MS_RCPSP_CROSSOVER_H
