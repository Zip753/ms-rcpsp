#include "../include/TabuSearchAlgorithm.h"

#include <deque>
#include <iostream>
#include <set>

template <class T>
bool TabuEquals(const T &a, const T &b) {
  for (int i = 0; i < a.size(); ++i) {
    if (a.ires[i] != b.ires[i]) return false;
  }
  return true;
}

template <class T>
bool TabuHit(const T& x, const std::deque<T>& tabu) {
  for (auto& el : tabu) {
    if (TabuEquals(x, el)) return true;
  }
  return false;
}

template <class T>
std::unique_ptr<T> TabuSearchAlgorithm<T>::optimize() {
  T start = T();
  T global_best = start;
  std::deque<T> tabu;
  for (int iter = 0; iter < iters_; ++iter) {
    tabu.push_back(start);
    if (iter >= list_size_) {
      tabu.pop_front();
    }
    T iter_best;
    bool first = true;
    for (int j = 0; j < neighbours_; ++j) {
      std::unique_ptr<T> neigbour = GenerateNeigbour(start);
      if (!TabuHit(*neigbour, tabu) &&
          (first || neigbour->fitness() < iter_best.fitness())) {
        iter_best = *neigbour;
        first = false;
      }
    }
    start = iter_best;
    std::cout << "iter: " << iter << ", fitness: " << start.fitness() << "\n";
    if (global_best.fitness() > iter_best.fitness()) {
      global_best = iter_best;
    }
  }
  return std::make_unique<T>(global_best);
}

template <class T>
std::unique_ptr<T> TabuSearchAlgorithm<T>::GenerateNeigbour(const T &start) {
  return std::move(mutator->mutate(start));
}
