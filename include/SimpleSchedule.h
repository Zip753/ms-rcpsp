#ifndef MS_RCPSP_SIMPLESCHEDULE_H
#define MS_RCPSP_SIMPLESCHEDULE_H

#include "Schedule.h"

/**
 * Class that represents the specimen in the scheduling problem.
 */
class SimpleSchedule : public Schedule {
 public:
  SimpleSchedule();

  /**
   * Creates schedule using given resource assignment.
   * @param _ires List of resource assignments.
   */
  SimpleSchedule(int *_ires);

  /**
   * Creates a copy of given SimpleSchedule.
   */
  SimpleSchedule(SimpleSchedule *s);

  ~SimpleSchedule();

  /**
   * List of relative business for each resource. Used to implement
   * LAXCrossover.
   */
  int *business;

 private:
  /**
   * Helper list, used in SimpleSchedule::update_start().
   */
  bool *visited;

  /**
   * Constructor hook, to keep constructors DRY.
   * @param create_ires If true, allocates resource list.
   */
  void init(bool create_ires);

  /**
   * Recursive function to update start time of a task.
   * @param i index of the task
   */
  void update_start(int i);

  /** Critical path fix procedure. */
  void reschedule();

  /** Schedule builder. Builds feasible schedule with no conflicts. */
  void fix_all();

  void compute_fitness();
};

#endif  // MS_RCPSP_SIMPLESCHEDULE_H
