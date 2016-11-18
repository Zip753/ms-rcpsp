#include "../include/Project.h"

#include <array>
#include <memory>
#include <vector>

namespace SchedulingProblem {

Project::Project(const std::vector<Task> &tasks_,
                 const std::vector<int> &res_id_,
                 const std::vector<double> &res_salary_)
    : tasks_(tasks_), res_id_(res_id_), res_salary_(res_salary_) {

  /* Create list of inverse dependencies. */
  std::vector<std::vector<size_t>> next(tasks_.size());
  for (auto& el : next) { el = std::vector<size_t>(); }

  for (size_t i = 0; i < tasks_.size(); ++i) {
    for (size_t j = 0; j < tasks_[i].num_dependencies(); ++j) {
      size_t idep = task(i).dependency(j);
      next[idep].push_back(i);
    }
  }

  for (size_t i = 0; i < tasks_.size(); ++i) {
    task(i).next = next[i];
  }
}

};  // namespace SchedulingProblem
