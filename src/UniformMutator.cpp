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
  size_t max_ires = sample->task(i).num_capable_resources();
  if (max_ires > 1) {
    size_t new_res = Random::randint() % (max_ires - 1);
    if (new_res < sample->capable_resource_idx(i))
      sample->set_capable_resource_idx(i, new_res);
    else
      sample->set_capable_resource_idx(i, new_res + 1);
  }
}

template<>
std::unique_ptr<PrioSchedule> UniformMutator<PrioSchedule>::Mutate(
    const PrioSchedule& sample) const {
  std::unique_ptr<PrioSchedule> s = std::make_unique<PrioSchedule>(sample);

  for (size_t i = 0; i < s->size(); i++) {
    // don't forget to check whether we can mutate it at all
    if (should_mutate()) {
      MutateGene(s.get(), i);
    }

    if (should_mutate()) {
      if (Random::rand(0.5)) {
        s->set_priority(i, s->priority(i) + 1);
      } else {
        s->set_priority(i, s->priority(i) - 1);
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
  size_t max_ires = sample->task(i).num_capable_resources();
  if (max_ires > 1) {
    size_t new_res = Random::randint() % (max_ires - 1);
    if (new_res < sample->capable_resource_idx(i))
      sample->set_capable_resource_idx(i, new_res);
    else
      sample->set_capable_resource_idx(i, new_res + 1);
  }
}

template<>
std::unique_ptr<SimpleSchedule> UniformMutator<SimpleSchedule>::Mutate(
    const SimpleSchedule& sample) const {
  std::unique_ptr<SimpleSchedule> s = std::make_unique<SimpleSchedule>(sample);

  for (size_t i = 0; i < s->size(); i++) {
    // don't forget to check whether we can mutate it at all
    if (should_mutate()) {
      MutateGene(s.get(), i);
    }
  }
  return s;
}

template class UniformMutator<SimpleSchedule>;

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions
