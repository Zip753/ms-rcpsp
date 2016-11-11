#include "../include/SimulatedAnnealingAlgorithm.h"

#include <cmath>
#include <iostream>

template <class T>
bool can_accept(T &next, T &prev, double temp) {
  return Random::rand(1 / (1 + exp((next.fitness() - prev.fitness()) / temp)));
}

template <class T>
std::unique_ptr<T> SimulatedAnnealingAlgorithm<T>::optimize(FILE* stream) {
  T start = T();
  double a = (log(start_temp_) - log(eps_)) / iters_;
  for (size_t iter = 0; iter < iters_; ++iter) {
    double temp = start_temp_ * exp(-(iter * a));
    std::unique_ptr<T> next = GenerateNeigbour(start);
    if (next->fitness() < start.fitness() || can_accept(*next, start, temp)) {
      start = *next;
    }
    fprintf(stream, "%d %lf\n", start.fitness(), temp);
    std::cout << "iter: " << iter << ", fitness: " << start.fitness()
        << ", temp: " << temp << "\n";
  }
  return std::make_unique<T>(start);
}

template <class T>
std::unique_ptr<T> SimulatedAnnealingAlgorithm<T>::GenerateNeigbour(
    const T &start) {
  return std::move(mutator_->mutate(start));
}
