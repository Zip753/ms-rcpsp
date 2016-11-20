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
  SimpleSchedule(const SimpleSchedule& s);
  ~SimpleSchedule() override {}

  /** Checks schedule equality in terms of representation. */
  bool operator==(const SimpleSchedule &other) const;

 private:
  /**
   * Contructor helper.
   * @param initialize If true, allocate and initialize resources.
   */
  void Init(bool create_ires);

  /**
   * Update start time of a task recursively.
   * @param i index of the task.
   * @param visited list of tasks visited by this function earlier.
   */
  void UpdateStart(size_t i, std::vector<bool> &visited);

  /** Critical path fix procedure. */
  void Reschedule();

  /** Schedule builder. Builds feasible schedule with no conflicts. */
  void FixAll();

  int ComputeDuration() override;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_SIMPLESCHEDULE_H
