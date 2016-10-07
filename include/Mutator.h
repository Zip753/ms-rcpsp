#ifndef MS_RCPSP_MUTATOR_H
#define MS_RCPSP_MUTATOR_H

template <class T>
class Mutator {
 public:
  Mutator(double _p_mut) : p_mut(_p_mut) {};
  // create new sample that is a probable mutation of given one
  T *mutate(T *sample);
  // mutate given sample without creating a new one
  void force_mutate(T *sample);

 private:
  double p_mut;
  void mutate_gene(T *sample, int idx);
};

#endif // MS_RCPSP_MUTATOR_H
