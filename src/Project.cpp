#include "../include/Project.h"

#include <array>
#include <memory>
#include <vector>

namespace SchedulingProblem {

std::unique_ptr<Project> Project::project_ = nullptr;

void Project::create(size_t _n,
                     const std::vector<Task> &_tasks,
                     size_t _res_count,
                     const std::vector<int> &_res_id,
                     const std::vector<double> &_res_sal) {
  project_ = std::unique_ptr<Project>(
      new Project(_n, _tasks, _res_count, _res_id, _res_sal));

  /* Create list of inverse dependency_. */
  std::vector<std::vector<size_t>> next(_n);
  for (auto& el : next) { el = std::vector<size_t>(); }

  for (size_t i = 0; i < _n; ++i) {
    for (size_t j = 0; j < _tasks[i].num_dependencies(); ++j) {
      size_t idep = task(i).dependency(j);
      next[idep].push_back(i);
    }
  }

  for (size_t i = 0; i < _n; ++i) {
    task(i).next = next[i];
  }
}

};  // namespace SchedulingProblem
