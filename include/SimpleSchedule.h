#ifndef MS_RCPSP_SIMPLESCHEDULE_H
#define MS_RCPSP_SIMPLESCHEDULE_H

#include "Schedule.h"

namespace SchedulingProblem {

/**
 * @brief Simple representation of schedule.
 *
 * This representation uses schedule builder procedure to find a feasible
 * schedule given the resource assignment and then calculate the fitness
 * function (project execution time) based on the found schedule.
 */
class SimpleSchedule : public Schedule {
 public:
  SimpleSchedule();
  SimpleSchedule(int* _ires);
  SimpleSchedule(SimpleSchedule* s);
  ~SimpleSchedule() override;

  /**
   * List of relative business for each resource. Used to implement
   * LAXCrossover.
   */
  int* business;

  /** Checks schedule equality in terms of representation. */
  bool operator==(SimpleSchedule s) const;

  void reset() override;

 private:
  /** Helper list, used in SimpleSchedule#update_start. */
  bool* visited;

  /**
   * Contructor helper.
   * @param initialize If true, allocate and initialize resources.
   */
  void init(bool create_ires);

  /**
   * Update start time of a task recursively.
   * @param i Index of the task.
   */
  void update_start(int i);

  /** Critical path fix procedure. */
  void reschedule();

  /** Schedule builder. Builds feasible schedule with no conflicts. */
  void fix_all();

  int compute_fitness() override;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_SIMPLESCHEDULE_H
