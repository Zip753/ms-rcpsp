#include "../include/Mutator.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

template <class T>
void Mutator<T>::force_mutate(Schedule* sample) {
  int idx = Random::randint() % sample->size();
  mutate_gene(dynamic_cast<T*>(sample), idx);
}

/************************************
 * Specialization for PrioSchedule: *
 ************************************/

template<>
void Mutator<PrioSchedule>::mutate_gene(PrioSchedule* sample, int i) {
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
PrioSchedule* Mutator<PrioSchedule>::mutate(PrioSchedule* sample) {
  PrioSchedule *s = new PrioSchedule(sample);

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

template class Mutator<PrioSchedule>;

/**************************************
 * Specialization for SimpleSchedule: *
 **************************************/

template<>
void Mutator<SimpleSchedule>::mutate_gene(SimpleSchedule* sample, int i) {
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
SimpleSchedule* Mutator<SimpleSchedule>::mutate(SimpleSchedule* sample) {
  SimpleSchedule *s = new SimpleSchedule(sample);

  for (int i = 0; i < s->size(); i++) {
    // don't forget to check whether we can mutate it at all
    if (Random::rand(p_mut)) {
      mutate_gene(s, i);
    }
  }
  return s;
}

template class Mutator<SimpleSchedule>;
