#include "../include/UniformCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

using SchedulingProblem::PrioSchedule;

template<>
std::unique_ptr<PrioSchedule> UniformCrossover<PrioSchedule>::Cross(
    const PrioSchedule& a, const PrioSchedule& b) const {
  std::unique_ptr<PrioSchedule> s = std::make_unique<PrioSchedule>(a);

  size_t n = s->size();
  for (size_t i = 0; i < n; i++) {
    if (Random::randint() % 2 == 1) {
      s->ires[i] = b.ires[i];
    }

    if (Random::randint() % 2 == 1) {
      s->prio[i] = b.prio[i];
    }
  }

  return std::move(s);
}

using SchedulingProblem::SimpleSchedule;

template<>
std::unique_ptr<SimpleSchedule> UniformCrossover<SimpleSchedule>::Cross(
    const SimpleSchedule& a, const SimpleSchedule& b) const {
  std::unique_ptr<SimpleSchedule> s = std::make_unique<SimpleSchedule>(a);

  size_t n = s->size();
  for (size_t i = 0; i < n; i++) {
    if (Random::randint() % 2 == 1) {
      s->ires[i] = b.ires[i];
    }
  }

  return std::move(s);
}

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions
