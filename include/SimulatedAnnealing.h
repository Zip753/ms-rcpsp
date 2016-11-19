#ifndef MS_RCPSP_SIMULATEDANNEALINGALGORITHM_H_
#define MS_RCPSP_SIMULATEDANNEALINGALGORITHM_H_

#include "Algorithm.h"
#include "Mutator.h"
#include "UniformMutator.h"

using Solutions::EvolutionaryAlgorithm::Mutator;
using Solutions::EvolutionaryAlgorithm::UniformMutator;

namespace Solutions {

template <class T>
class SimulatedAnnealing : public Algorithm<T> {
 public:
  std::unique_ptr<T> optimize(std::ostream &stream) override;
  SimulatedAnnealing(const T &&start_, size_t iters_,
                              double start_temp_, double p_mut,
                              double eps_ = 1e-7) :
      start_(start_), iters_(iters_), start_temp_(start_temp_),
      mutator_(std::make_unique<UniformMutator<T>>(p_mut)), eps_(eps_) {}

 private:
  T start_;
  const size_t iters_;
  const double start_temp_;
  std::shared_ptr<Mutator<T>> mutator_;
  const double eps_;

  std::unique_ptr<T> GenerateNeigbour(const T &start);
};

};  // namespace Solutions

#include "../src/SimulatedAnnealing.tpp"

#endif  // MS_RCPSP_SIMULATEDANNEALINGALGORITHM_H_
