#ifndef MS_RCPSP_PROJECT_H
#define MS_RCPSP_PROJECT_H

#include <memory>
#include <vector>

#include "Resource.h"
#include "Task.h"

namespace SchedulingProblem {

/**
 * @brief Singleton representation of project in the scheduling problem.
 */
class Project {

 public:
  Project(const std::vector<Task> &tasks_,
          const std::vector<Resource> &resource_) :
      tasks_(tasks_), resource_(resource_) {}

  /** @return number of tasks in the project. */
  inline size_t size() const { return tasks_.size(); }

  /** @return number of resources. */
  inline size_t num_resources() const { return resource_.size(); }

  /**
   * Returns resource at the given index.
   * @param i index of the resource.
   */
  inline Resource& resource(size_t i) { return resource_.at(i); }

  Task& task(size_t i) { return tasks_.at(i); }

 private:
  /** List of project tasks. */
  std::vector<Task> tasks_;
  /** List of resources. */
  std::vector<Resource> resource_;
};

};  // namespace SchedulingProblem

#endif  // MS_RCPSP_PROJECT_H
