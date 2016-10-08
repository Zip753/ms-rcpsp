#include "../include/Population.h"

Population::~Population() {
  for (int i = 0; i < n; i++)
    delete genotype[i];
  delete[] genotype;
}

int Population::size() {
  return n;
}

Schedule* Population::best() {
  Schedule* ans = genotype[0];
  for (int i = 1; i < n; i++) {
    if (genotype[i]->fitness() < ans->fitness())
      ans = genotype[i];
  }
  return ans;
}

void Population::showStat(FILE* stream) {
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
