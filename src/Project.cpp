#include "../include/Project.h"

#include <memory>
#include <vector>

namespace SchedulingProblem {

std::shared_ptr<Project> Project::_project = nullptr;

void Project::create(int _n, Task **_tasks, int _res_count, int *_res_id,
                     double *_res_sal) {
  _project = std::shared_ptr<Project>(
      new Project(_n, _tasks, _res_count, _res_id, _res_sal));

  /* Create list of inverse dependencies. */
  std::vector<int> *next = new std::vector<int>[_n];

  for (int i = 0; i < _n; ++i) {
    for (int j = 0; j < _tasks[i]->dep_size(); ++j) {
      int idep = _tasks[i]->dep[j];
      next[idep].push_back(i);
    }
  }

  for (int i = 0; i < _n; ++i) {
    int size = static_cast<int>(next[i].size());
    _tasks[i]->next_size = size;
    _tasks[i]->next = new int[size];
    for (int j = 0; j < size; ++j) {
      _tasks[i]->next[j] = next[i][j];
    }
  }

  delete[] next;
}

Project::~Project() {
  for (int i = 0; i < n; i++) delete tasks[i];
  delete[] tasks;
  delete[] res_id;
  delete[] res_salary;
}

};  // namespace SchedulingProblem
