#include "../include/SimulatedAnnealing.h"

#include <cmath>
#include <iostream>

namespace Solutions {

template <class T>
bool can_accept(T &next, T &prev, double temp) {
  return Random::rand(1 / (1 + exp((next.Fitness() - prev.Fitness()) / temp)));
}

template <class T>
std::unique_ptr<T> SimulatedAnnealing<T>::Optimize(
    std::ostream &stream) {
  T start = start_;
  double a = (log(start_temp_) - log(eps_)) / iters_;
  for (size_t iter = 0; iter < iters_; ++iter) {
    double temp = start_temp_ * exp(-(iter * a));
    std::unique_ptr<T> next = GenerateNeigbour(start);
    if (next->Fitness() < start.Fitness() || can_accept(*next, start, temp)) {
      start = *next;
    }
    stream << start.Fitness() << " " << temp << "\n";
    std::cout << "iter: " << iter << ", fitness: " << start.Fitness()
        << ", temp: " << temp << "\n";
  }
  return std::make_unique<T>(start);
}

template <class T>
std::unique_ptr<T> SimulatedAnnealing<T>::GenerateNeigbour(
    const T &start) {
  return mutator_->Mutate(start);
}

};  // namespace Solutions
