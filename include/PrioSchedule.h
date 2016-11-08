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
  PrioSchedule();
  PrioSchedule(std::vector<int> _ires, std::vector<int> _prio);
  PrioSchedule(const PrioSchedule& s);
  ~PrioSchedule() override {}

  int compute_fitness() override;

  /** Task priorities. */
  std::vector<int> prio;

  /** Checks schedule equality in terms of representation. */
  bool operator==(PrioSchedule s) const;

  void reset() override;

  /** Businesses of resources. Used to implement LAXCrossover. */
  std::vector<int> business;

 private:
  /**
   * Contructor helper.
   * @param initialize If true, allocate and initialize resources and
   * priorities.
   */
  void init(bool initialize);

  /** Schedule builder. Builds feasible schedule with no conflicts. */
  void fix_all();
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PRIOSCHEDULE_H
