#ifndef MS_RCPSP_TABUSEARCHALGORITHM_H_
#define MS_RCPSP_TABUSEARCHALGORITHM_H_

#include "Algorithm.h"
#include "Mutator.h"

using EvolutionaryAlgorithm::SimpleMutator;

template <class T>
class TabuSearchAlgorithm : public EvolutionaryAlgorithm::Algorithm<T> {
 public:
  std::unique_ptr<T> optimize(FILE* stream) override;
  TabuSearchAlgorithm(size_t iters_, size_t neighbours_, size_t list_size_,
                      double p_mut) :
      iters_(iters_), neighbours_(neighbours_), list_size_(list_size_),
      mutator(std::make_unique<SimpleMutator<T>>(p_mut)) {}

 private:
  size_t iters_;
  size_t neighbours_;
  size_t list_size_;
  std::shared_ptr<EvolutionaryAlgorithm::Mutator<T>> mutator;

  std::unique_ptr<T> GenerateNeigbour(const T& start);
};

#include "../src/TabuSearchAlgorithm.tpp"

#endif  // MS_RCPSP_TABUSEARCHALGORITHM_H_
