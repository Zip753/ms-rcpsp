#ifndef MS_RCPSP_PROJECT_H
#define MS_RCPSP_PROJECT_H

#include <memory>

#include "Task.h"

/**
 * @brief Singleton representation of project in the scheduling problem.
 */
class Project {

 public:
  /** Creates singleton instance. */
  static void create(int _n, Task **_tasks, int _res_count, int* _res_id,
                     double* _res_sal);

  /** @return Pointer to project instance. */
  inline static std::shared_ptr<Project> get() { return _project; }

  /** Returns the number of tasks in the project. */
  inline int size() { return n; }

  /** Returns number of resources. */
  inline int get_res_count() { return res_count; }

  /**
   * Returns resource ID of the resource at the given index.
   * @param res index of the resource
   */
  inline int get_res_id(int res) { return res_id[res]; }

  /**
   * Returns the hourly salary of the resource at the given index.
   * @param res index of the resource
   */
  inline double get_salary(int res) { return res_salary[res]; }

  ~Project();

  /** List of project tasks. */
  Task** tasks;

 private:
  /** Number of tasks. */
  int n;
  /** IDs of resources. */
  int* res_id;
  /** Salaries of resources. */
  double* res_salary;
  /** Number of resources. */
  int res_count;
  /** Shortcut to Project. */
  static std::shared_ptr<Project> _project;
  /** @see ProjectReader::read() */
  Project(int _n, Task** _tasks, int _res_count, int* _res_id,
          double* _res_sal)
      : tasks(_tasks), n(_n), res_id(_res_id), res_salary(_res_sal),
        res_count(_res_count) {}
};

#endif  // MS_RCPSP_PROJECT_H
