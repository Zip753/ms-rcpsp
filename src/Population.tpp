#include "../include/Population.h"

template <class T>
Population<T>::~Population() {
  for (int i = 0; i < n; i++)
    delete genotype[i];
  delete[] genotype;
}

template <class T>
T* Population<T>::best() {
  T* ans = genotype[0];
  for (int i = 1; i < n; i++) {
    if (genotype[i]->fitness() < ans->fitness())
      ans = genotype[i];
  }
  return ans;
}

template <class T>
void Population<T>::showStat(FILE* stream) {
  int best_val = best()->fitness(),
      worst_val = 0;
  double mean = 0;
  for (int i = 0; i < n; i++) {
    mean += genotype[i]->fitness();
    if (worst_val < genotype[i]->fitness())
      worst_val = genotype[i]->fitness();
  }
  mean /= n;

  fprintf(stream, "%d %.4lf %d\n", best_val, mean, worst_val);
}
