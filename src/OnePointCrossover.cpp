#include "../include/OnePointCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

using SchedulingProblem::SimpleSchedule;

template<>
std::unique_ptr<SimpleSchedule> OnePointCrossover<SimpleSchedule>::cross(
    const SimpleSchedule& a, const SimpleSchedule& b) const {
  std::unique_ptr<SimpleSchedule> s = std::make_unique<SimpleSchedule>(a);

  int n = s->size();
  int idx = Random::randint() % n;
  for (int i = idx; i < n; i++) {
    s->ires[i] = b.ires[i];
  }

  return std::move(s);
}

using SchedulingProblem::PrioSchedule;

template<>
std::unique_ptr<PrioSchedule> OnePointCrossover<PrioSchedule>::cross(
    const PrioSchedule& a, const PrioSchedule& b) const {
  std::unique_ptr<PrioSchedule> s = std::make_unique<PrioSchedule>(a);

  int n = s->size();
  int idx = Random::randint() % n;
  for (int i = idx; i < n; i++)
    s->ires[i] = b.ires[i];

  return std::move(s);
}

};  // namespace EvolutionaryAlgorithm
