#ifndef MS_RCPSP_SIMPLESCHEDULE_H
#define MS_RCPSP_SIMPLESCHEDULE_H

#include "Businessable.h"
#include "Schedule.h"

namespace SchedulingProblem {

/**
 * @brief Simple representation of schedule.
 *
 * This representation uses schedule builder procedure to find a feasible
 * schedule given the resource assignment and then calculate the fitness
 * function (project execution time) based on the found schedule.
 */
class SimpleSchedule : public Schedule, public Businessable {
 public:
  SimpleSchedule(Project* project_);
  SimpleSchedule(const SimpleSchedule& s) : Schedule(s), Businessable(s) {}
  ~SimpleSchedule() override {}

  /** Checks schedule equality in terms of representation. */
  bool operator==(const SimpleSchedule &other) const;

 private:
  /** Schedule builder. Builds feasible schedule with no conflicts. */
  void FixAll();

  int ComputeDuration() override;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_SIMPLESCHEDULE_H
