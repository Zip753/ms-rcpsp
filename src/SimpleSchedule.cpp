#include "../include/SimpleSchedule.h"

#include <algorithm>
#include <queue>
#include <vector>

#include "../include/Project.h"

namespace SchedulingProblem {

bool SimpleSchedule::operator==(const SimpleSchedule &other) const {
  return Schedule::operator==(other);
}

SimpleSchedule::SimpleSchedule(Project* project_)
    : Schedule(project_), Businessable(project_->size()) {
  Reset();
}

void SimpleSchedule::FixAll() {
  /* Create list of inverse dependencies. */
  std::vector<std::vector<size_t>> next(size_);
  for (auto& el : next) { el = std::vector<size_t>(); }

  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < project_->task(i).num_dependencies(); ++j) {
      size_t idep = task(i).dependency(j);
      next[idep].push_back(i);
    }
  }

  // heap of pairs (task_id, priority)
  std::queue<size_t> queue;
  for (size_t i = 0; i < size_; ++i) {
    if (task(i).num_dependencies() == 0) {
      queue.push(i);
    }
  }
  size_t res_count = project_->num_resources();

  // availability time for resource_
  std::vector<int> time(res_count);

  // number of complete dependency_ for tasks
  std::vector<size_t> dep_count(size_);

  while (!queue.empty()) {
    // take next task
    size_t itask = queue.front();
    queue.pop();

    // find max finish time of all dependency_
    size_t res_idx = resource_idx(itask);
    int min_start = 0;
    for (size_t i = 0; i < task(itask).num_dependencies(); ++i) {
      size_t idep = task(itask).dependency(i);
      int fin = finish_time(idep) + 1;
      if (min_start < fin)
        min_start = fin;
    }

    // update start time for the task
    start_[itask] = std::max(min_start, time[res_idx]);
    // update availability time for resource
    time[res_idx] = finish_time(itask) + 1;

    // add all unblocked dependent tasks to the queue
    for (size_t i = 0; i < next[itask].size(); ++i) {
      size_t inext = next[itask][i];
      dep_count[inext]++;
      if (dep_count[inext] == task(inext).num_dependencies()) {
        queue.push(inext);
      }
    }
  }
}

int SimpleSchedule::ComputeDuration() {
  FixAll();

  int duration = -1;
  for (size_t i = 0; i < size_; i++) {
    int finish = finish_time(i);
    if (duration < finish)
      duration = finish;
  }

  std::fill(business_.begin(), business_.end(), 0);
  for (size_t i = 0; i < size_; i++) {
    size_t res_idx = resource_idx(i);
    business_[res_idx] += task(i).duration();
  }

  return duration;
}

};  // namespace SchedulingProblem
