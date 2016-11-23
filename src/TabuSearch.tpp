#include "../include/TabuSearch.h"

#include <cassert>
#include <deque>
#include <iostream>
#include <set>

namespace Solutions {

template <class T>
bool TabuEquals(const T &a, const T &b) {
  for (size_t i = 0; i < a.size(); ++i) {
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
std::unique_ptr<T> TabuSearch<T>::Optimize(std::ostream &stream) {
  T start = start_;
  T global_best = start;
  std::deque<T> tabu;
  for (size_t iter = 0; iter < iters_; ++iter) {
    tabu.push_back(start);
    if (iter >= list_size_) {
      tabu.pop_front();
    }
    std::unique_ptr<T> iter_best = nullptr;
    bool first = true;
    double mean = 0;
    int worst_val = 0;
    size_t hits = 0;
    for (size_t j = 0; j < neighbours_; ++j) {
      std::unique_ptr<T> neigbour = GenerateNeigbour(start);
      mean += neigbour->Fitness();
      if (worst_val < neigbour->Fitness()) {
        worst_val = neigbour->Fitness();
      }
      if (TabuHit(*neigbour, tabu)) {
        ++hits;
      } else if (first || neigbour->Fitness() < iter_best->Fitness()) {
        iter_best = std::move(neigbour);
        first = false;
      }
    }
    assert(iter_best != nullptr);
    mean /= neighbours_;
    stream << iter_best->Fitness() << " " << mean << " " << worst_val << " "
           << static_cast<double>(hits) / neighbours_ << "\n";
    start = *iter_best;
    std::cout << "iter: " << iter << ", fitness: " << start.Fitness() << "\n";
    if (global_best.Fitness() > iter_best->Fitness()) {
      global_best = *iter_best;
    }
  }
  return std::make_unique<T>(global_best);
}

template <class T>
std::unique_ptr<T> TabuSearch<T>::GenerateNeigbour(const T &start) {
  return std::move(mutator_->Mutate(start));
}

};  // namespace Solutions
