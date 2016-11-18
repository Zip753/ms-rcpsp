#ifndef MS_RCPSP_SIMULATEDANNEALINGALGORITHM_H_
#define MS_RCPSP_SIMULATEDANNEALINGALGORITHM_H_

#include "Algorithm.h"
#include "Mutator.h"
#include "UniformMutator.h"

using EvolutionaryAlgorithm::Mutator;
using EvolutionaryAlgorithm::UniformMutator;

template <class T>
class SimulatedAnnealingAlgorithm : public EvolutionaryAlgorithm::Algorithm<T> {
 public:
  std::unique_ptr<T> optimize(std::ostream &stream) override;
  SimulatedAnnealingAlgorithm(size_t iters_, double start_temp_, double p_mut,
                              double eps_ = 1e-7) :
      iters_(iters_), start_temp_(start_temp_),
      mutator_(std::make_unique<UniformMutator<T>>(p_mut)), eps_(eps_) {}

 private:
  const size_t iters_;
  const double start_temp_;
  std::shared_ptr<EvolutionaryAlgorithm::Mutator<T>> mutator_;
  const double eps_;

  std::unique_ptr<T> GenerateNeigbour(const T &start);
};

#include "../src/SimulatedAnnealingAlgorithm.tpp"

#endif  // MS_RCPSP_SIMULATEDANNEALINGALGORITHM_H_
