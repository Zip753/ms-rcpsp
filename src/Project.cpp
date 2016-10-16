#include "../include/Project.h"

#include <memory>
#include <vector>

namespace SchedulingProblem {

std::unique_ptr<Project> Project::_project = nullptr;

void Project::create(int _n,
                     const std::vector<Task*> &_tasks,
                     int _res_count,
                     const std::vector<int> &_res_id,
                     const std::vector<double> &_res_sal) {
  _project = std::unique_ptr<Project>(
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
    _tasks[i]->next = next[i];
  }

  delete[] next;
}

Project::~Project() {
  for (int i = 0; i < n; i++) delete tasks[i];
}

};  // namespace SchedulingProblem
