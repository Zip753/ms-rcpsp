#ifndef MS_RCPSP_PROJECT_H
#define MS_RCPSP_PROJECT_H

#include "Task.h"

class Project {
 public:
  static void create(int _n, Task **_tasks, int _res_count, int *_res_id,
                     double *_res_sal);
  static void remove();
  static Project *get();
  ~Project();

  int size();
  int get_res_count();
  int get_res_id(int res);
  double get_salary(int res);
  Task **tasks;

 private:
  int n;
  int *res_id;
  double *res_salary;
  int res_count;
  static Project *_project;
  Project(int _n, Task **_tasks, int _res_count, int *_res_id, double *_res_sal)
      : tasks(_tasks), n(_n), res_id(_res_id), res_salary(_res_sal),
        res_count(_res_count) {};
};

#endif // MS_RCPSP_PROJECT_H
