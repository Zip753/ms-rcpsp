#ifndef MS_RCPSP_PRIOSCHEDULE_H
#define MS_RCPSP_PRIOSCHEDULE_H

#include <cstdio>
#include <set>
#include <utility>

#include "Businessable.h"
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
class PrioSchedule : public Schedule, public Businessable {
 public:
  PrioSchedule(Project* project_);
  PrioSchedule(const PrioSchedule& s);
  ~PrioSchedule() override {}

  void Reset() override;

  /** Checks schedule equality in terms of representation. */
  bool operator==(const PrioSchedule &other) const;

  inline int priority(size_t i) const { return priority_[i]; }

  inline void set_priority(size_t i, int new_priority) {
    priority_[i] = new_priority;
  }

 private:
  /** Task priorities. */
  std::vector<int> priority_;

  /**
   * Contructor helper.
   * @param initialize If true, allocate and initialize resources and
   * priorities.
   */
  void Init(bool initialize);

  /** Schedule builder. Builds feasible schedule with no conflicts. */
  void FixAll();

  int ComputeDuration() override;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PRIOSCHEDULE_H
