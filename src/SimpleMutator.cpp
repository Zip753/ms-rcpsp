#include "../include/SimpleMutator.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

/************************************
 * Specialization for PrioSchedule: *
 ************************************/

using SchedulingProblem::PrioSchedule;

template<>
void SimpleMutator<PrioSchedule>::mutate_gene(PrioSchedule* sample, int i)
    const {
  int max_ires = sample->max_res_count(i);
  if (max_ires > 1) {
    int new_res = Random::randint() % (max_ires - 1);
    if (new_res < sample->ires[i])
      sample->ires[i] = new_res;
    else
      sample->ires[i] = new_res + 1;
  }
}

template<>
PrioSchedule* SimpleMutator<PrioSchedule>::mutate(PrioSchedule* sample) const {
  PrioSchedule* s = new PrioSchedule(sample);

  for (int i = 0; i < s->size(); i++) {
    // don't forget to check whether we can mutate it at all
    if (Random::rand(p_mut)) {
      mutate_gene(s, i);
    }

    if (Random::rand(p_mut)) {
      if (Random::rand(0.5)) {
        ++sample->prio[i];
      } else {
        --sample->prio[i];
      }
    }
  }
  return s;
}

template class SimpleMutator<PrioSchedule>;

/**************************************
 * Specialization for SimpleSchedule: *
 **************************************/

using SchedulingProblem::SimpleSchedule;

template<>
void SimpleMutator<SimpleSchedule>::mutate_gene(SimpleSchedule* sample, int i)
    const {
  int max_ires = sample->max_res_count(i);
  if (max_ires > 1) {
    int new_res = Random::randint() % (max_ires - 1);
    if (new_res < sample->ires[i])
      sample->ires[i] = new_res;
    else
      sample->ires[i] = new_res + 1;
  }
}

template<>
SimpleSchedule* SimpleMutator<SimpleSchedule>::mutate(SimpleSchedule* sample)
    const {
  SimpleSchedule* s = new SimpleSchedule(sample);

  for (int i = 0; i < s->size(); i++) {
    // don't forget to check whether we can mutate it at all
    if (Random::rand(p_mut)) {
      mutate_gene(s, i);
    }
  }
  return s;
}

template class SimpleMutator<SimpleSchedule>;

};  // namespace EvolutionaryAlgorithm
