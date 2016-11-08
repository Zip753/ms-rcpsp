#include "../include/LAXCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Project.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace EvolutionaryAlgorithm {

using SchedulingProblem::PrioSchedule;
using SchedulingProblem::Project;

template<>
std::unique_ptr<PrioSchedule> LAXCrossover<PrioSchedule>::cross(
    const PrioSchedule& a, const PrioSchedule& b) const {
  int n = a.size();
  std::vector<int> ires = std::vector<int>(n);
  std::vector<int> prio = std::vector<int>(n);
  for (int i = 0; i < n; i++) {
    int a_res = a.resource(i);
    int b_res = b.resource(i);
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
std::unique_ptr<SimpleSchedule> LAXCrossover<SimpleSchedule>::cross(
    const SimpleSchedule& a, const SimpleSchedule& b) const {
  int n = a.size();
  std::vector<int> ires = std::vector<int>(n);
  for (int i = 0; i < n; i++) {
    int a_res = a.resource(i);
    int b_res = b.resource(i);
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
