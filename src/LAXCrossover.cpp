#include "../include/LAXCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Project.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

namespace Solutions {
namespace EvolutionaryAlgorithm {

using SchedulingProblem::PrioSchedule;
using SchedulingProblem::Project;

template<>
std::unique_ptr<PrioSchedule> LAXCrossover<PrioSchedule>::Cross(
    const PrioSchedule& a, const PrioSchedule& b) const {
  std::unique_ptr<PrioSchedule> s = std::make_unique<PrioSchedule>(a);

  for (size_t i = 0; i < s->size(); i++) {
    size_t a_res = a.resource(i);
    size_t b_res = b.resource(i);
    if (a.business(a_res) < b.business(b_res)) {
      s->set_resource_idx(i, a.resource_idx(i));
    } else if (a.business(a_res) > b.business(b_res)) {
      s->set_resource_idx(i, b.resource_idx(i));
    } else {
      double a_sal = a.resource_salary(a_res);
      double b_sal = b.resource_salary(b_res);
      if (a_sal < b_sal)
        s->set_resource_idx(i, a.resource_idx(i));
      else
        s->set_resource_idx(i, b.resource_idx(i));
    }

    if (Random::randint() & 1) {
      s->set_priority(i, a.priority(i));
    } else {
      s->set_priority(i, b.priority(i));
    }
  }

  return std::move(s);
}

using SchedulingProblem::SimpleSchedule;

template<>
std::unique_ptr<SimpleSchedule> LAXCrossover<SimpleSchedule>::Cross(
    const SimpleSchedule& a, const SimpleSchedule& b) const {
  std::unique_ptr<SimpleSchedule> s = std::make_unique<SimpleSchedule>(a);

  for (size_t i = 0; i < s->size(); i++) {
    size_t a_res = a.resource(i);
    size_t b_res = b.resource(i);
    if (a.business(a_res) < b.business(b_res)) {
      s->set_resource_idx(i, a.resource_idx(i));
    } else if (a.business(a_res) > b.business(b_res)) {
      s->set_resource_idx(i, b.resource_idx(i));
    } else {
      double a_sal = a.resource_salary(a_res);
      double b_sal = b.resource_salary(b_res);
      if (a_sal < b_sal)
        s->set_resource_idx(i, a.resource_idx(i));
      else
        s->set_resource_idx(i, b.resource_idx(i));
    }
  }
  return std::move(s);
}

};  // namespace EvolutionaryAlgorithm
};  // namespace Solutions
