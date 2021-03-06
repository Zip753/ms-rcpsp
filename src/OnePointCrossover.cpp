#include "../include/OnePointCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

using SchedulingProblem::SimpleSchedule;

template<>
std::unique_ptr<SimpleSchedule> OnePointCrossover<SimpleSchedule>::Cross(
    const SimpleSchedule& a, const SimpleSchedule& b) const {
  std::unique_ptr<SimpleSchedule> s = std::make_unique<SimpleSchedule>(a);

  size_t n = s->size();
  size_t idx = Random::randint() % n;
  for (size_t i = idx; i < n; i++) {
    s->set_capable_resource_idx(i, b.capable_resource_idx(i));
  }

  return s;
}

using SchedulingProblem::PrioSchedule;

template<>
std::unique_ptr<PrioSchedule> OnePointCrossover<PrioSchedule>::Cross(
    const PrioSchedule& a, const PrioSchedule& b) const {
  std::unique_ptr<PrioSchedule> s = std::make_unique<PrioSchedule>(a);

  size_t n = s->size();
  size_t idx = Random::randint() % n;
  for (size_t i = idx; i < n; i++)
    s->set_capable_resource_idx(i, b.capable_resource_idx(i));

  return s;
}

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions
