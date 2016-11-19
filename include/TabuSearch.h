#ifndef MS_RCPSP_TABUSEARCHALGORITHM_H_
#define MS_RCPSP_TABUSEARCHALGORITHM_H_

#include "Algorithm.h"
#include "Mutator.h"

using Solutions::EvolutionaryAlgorithm::Mutator;
using Solutions::EvolutionaryAlgorithm::UniformMutator;

namespace Solutions {

template <class T>
class TabuSearch : public Algorithm<T> {
 public:
  std::unique_ptr<T> optimize(std::ostream &stream) override;
  TabuSearch(const T &&start_, size_t iters_, size_t neighbours_,
                      size_t list_size_, double p_mut) :
      start_(start_), iters_(iters_), neighbours_(neighbours_),
      list_size_(list_size_),
      mutator_(std::make_unique<UniformMutator<T>>(p_mut)) {}

 private:
  T start_;
  size_t iters_;
  size_t neighbours_;
  size_t list_size_;
  std::shared_ptr<Mutator<T>> mutator_;

  std::unique_ptr<T> GenerateNeigbour(const T& start);
};

};  // namespace Solutions

#include "../src/TabuSearch.tpp"

#endif  // MS_RCPSP_TABUSEARCHALGORITHM_H_
