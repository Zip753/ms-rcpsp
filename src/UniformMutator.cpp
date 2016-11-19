#include "../include/UniformMutator.h"

#include <memory>

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

/************************************
 * Specialization for PrioSchedule: *
 ************************************/

using SchedulingProblem::PrioSchedule;

template<>
void UniformMutator<PrioSchedule>::MutateGene(PrioSchedule* sample, size_t i)
    const {
  size_t max_ires = sample->max_res_count(i);
  if (max_ires > 1) {
    size_t new_res = Random::randint() % (max_ires - 1);
    if (new_res < sample->ires[i])
      sample->ires[i] = new_res;
    else
      sample->ires[i] = new_res + 1;
  }
}

template<>
std::unique_ptr<PrioSchedule> UniformMutator<PrioSchedule>::Mutate(
    const PrioSchedule& sample) const {
  std::unique_ptr<PrioSchedule> s = std::make_unique<PrioSchedule>(sample);

  for (size_t i = 0; i < s->size(); i++) {
    // don't forget to check whether we can mutate it at all
    if (Random::rand(p_mut)) {
      MutateGene(s.get(), i);
    }

    if (Random::rand(p_mut)) {
      if (Random::rand(0.5)) {
        ++s->prio[i];
      } else {
        --s->prio[i];
      }
    }
  }
  return s;
}

template class UniformMutator<PrioSchedule>;

/**************************************
 * Specialization for SimpleSchedule: *
 **************************************/

using SchedulingProblem::SimpleSchedule;

template<>
void UniformMutator<SimpleSchedule>::MutateGene(SimpleSchedule* sample,
                                                size_t i) const {
  size_t max_ires = sample->max_res_count(i);
  if (max_ires > 1) {
    size_t new_res = Random::randint() % (max_ires - 1);
    if (new_res < sample->ires[i])
      sample->ires[i] = new_res;
    else
      sample->ires[i] = new_res + 1;
  }
}

template<>
std::unique_ptr<SimpleSchedule> UniformMutator<SimpleSchedule>::Mutate(
    const SimpleSchedule& sample) const {
  std::unique_ptr<SimpleSchedule> s = std::make_unique<SimpleSchedule>(sample);

  for (size_t i = 0; i < s->size(); i++) {
    // don't forget to check whether we can mutate it at all
    if (Random::rand(p_mut)) {
      MutateGene(s.get(), i);
    }
  }
  return std::move(s);
}

template class UniformMutator<SimpleSchedule>;

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions
