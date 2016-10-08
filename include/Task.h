#ifndef MS_RCPSP_TASK_H
#define MS_RCPSP_TASK_H

/** @brief Representation of task. */
class Task {
 public:
  /**
   * @param _id ID of the task.
   * @param _dur Duration of the task.
   * @param _ndep Number of dependencies.
   * @param _dep List of dependencies.
   * @param _nres Number of capable resources.
   * @param _res List of capable resources.
   */
  Task(int _id, int _dur, int *_dep, int *_res, int _ndep, int _nres)
      : id(_id), duration(_dur), dep(_dep), res(_res), ndep(_ndep),
        nres(_nres) {}
  ~Task();

  /** Task ID, as specified in input file. */
  int id;
  /** Task duration. */
  int duration;
  /** List of dependencies, i.e. tasks that have to be completed before this
   * task. */
  int* dep;
  /** List of resources capable of completing the task. */
  int* res;
  /** List of inverse dependencies. */
  int* next;

  /** Returns number of resources capable of completing the task. */
  int res_size() const { return nres; }

  /** Returns number of dependencies, i.e. tasks that have to be completed
   * before this task. */
  int dep_size() const { return ndep; }

  /** Number of inverse dependencies. */
  int next_size;

 private:
  int ndep, nres;
};

#endif  // MS_RCPSP_TASK_H
