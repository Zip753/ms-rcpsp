#ifndef MS_RCPSP_PRIOSCHEDULE_H
#define MS_RCPSP_PRIOSCHEDULE_H

#include <cstdio>
#include <set>
#include <utility>

#include "Task.h"
#include "Schedule.h"

namespace SchedulingProblem {

/**
 * @brief Representation of schedule that uses task priorities.
 *
 * This schedule representation introduces task priorities, so that when a
 * resource can execute several tasks at some point, he always executes the
 * task with the biggest priority, as opposed to executing random task as in
 * SimpleSchedule.
 */
class PrioSchedule : public Schedule {
 public:
  PrioSchedule(Project* project_);
  PrioSchedule(const PrioSchedule& s);
  ~PrioSchedule() override {}

  int ComputeFitness() override;

  void Reset() override;

  /** Checks schedule equality in terms of representation. */
  bool operator==(PrioSchedule s) const;

  inline int priority(size_t i) const { return priority_[i]; }

  inline void set_priority(size_t i, int new_priority) {
    priority_[i] = new_priority;
  }

  inline int business(size_t i) const { return business_[i]; }

  inline void set_business(size_t i, int new_business) {
    business_[i] = new_business;
  }

 private:
  /** Task priorities. */
  std::vector<int> priority_;

  /** Businesses of resources. Used to implement LAXCrossover. */
  std::vector<int> business_;

  /**
   * Contructor helper.
   * @param initialize If true, allocate and initialize resources and
   * priorities.
   */
  void Init(bool initialize);

  /** Schedule builder. Builds feasible schedule with no conflicts. */
  void FixAll();
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PRIOSCHEDULE_H
