#include "../include/LAXCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Project.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

using SchedulingProblem::PrioSchedule;
using SchedulingProblem::Project;

template<>
std::unique_ptr<PrioSchedule> LAXCrossover<PrioSchedule>::Cross(
    const PrioSchedule& a, const PrioSchedule& b) const {
  size_t n = a.size();
  std::vector<size_t> ires = std::vector<size_t>(n);
  std::vector<int> prio = std::vector<int>(n);
  for (size_t i = 0; i < n; i++) {
    size_t a_res = a.resource(i);
    size_t b_res = b.resource(i);
    if (a.business[a_res] < b.business[b_res]) {
      ires[i] = a.ires[i];
    } else if (a.business[a_res] > b.business[b_res]) {
      ires[i] = b.ires[i];
    } else {
      double a_sal = Project::get_salary(a_res);
      double b_sal = Project::get_salary(b_res);
      if (a_sal < b_sal)
        ires[i] = a.ires[i];
      else
        ires[i] = b.ires[i];
    }

    if (Random::randint() & 1) {
      prio[i] = a.prio[i];
    } else {
      prio[i] = b.prio[i];
    }
  }

  return std::move(std::make_unique<PrioSchedule>(ires, prio));
}

using SchedulingProblem::SimpleSchedule;

template<>
std::unique_ptr<SimpleSchedule> LAXCrossover<SimpleSchedule>::Cross(
    const SimpleSchedule& a, const SimpleSchedule& b) const {
  size_t n = a.size();
  std::vector<size_t> ires = std::vector<size_t>(n);
  for (size_t i = 0; i < n; i++) {
    size_t a_res = a.resource(i);
    size_t b_res = b.resource(i);
    if (a.business[a_res] < b.business[b_res]) {
      ires[i] = a.ires[i];
    } else if (a.business[a_res] > b.business[b_res]) {
      ires[i] = b.ires[i];
    } else {
      double a_sal = Project::get_salary(a_res);
      double b_sal = Project::get_salary(b_res);
      if (a_sal < b_sal)
        ires[i] = a.ires[i];
      else
        ires[i] = b.ires[i];
    }
  }
  return std::move(std::make_unique<SimpleSchedule>(ires));
}

};  // namespace EvolutionaryAlgorithm
