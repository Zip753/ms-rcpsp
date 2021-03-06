#include "../include/PrioSchedule.h"

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "../include/Project.h"
#include "../include/Random.h"

namespace SchedulingProblem {

bool PrioSchedule::operator==(const PrioSchedule &other) const {
  if (!Schedule::operator==(other)) return false;
  for (size_t i = 0; i < size(); i++)
    if (priority_[i] != other.priority_[i])
      return false;
  return true;
}

PrioSchedule::PrioSchedule(Project* project_)
    : Schedule(project_), Businessable(project_->size()),
      priority_(std::vector<int>(size(), 0)) {
  Reset();
}

void PrioSchedule::FixAll() {
  struct PriorityComp {
    bool operator()(const std::pair<size_t, int> a,
                    const std::pair<size_t, int> b) const {
      return a.second < b.second;
    }
  };

  /* Create list of inverse dependencies. */
  std::vector<std::vector<size_t>> next(size());
  for (auto& el : next) { el = std::vector<size_t>(); }

  for (size_t i = 0; i < size(); ++i) {
    for (size_t j = 0; j < project_->task(i).num_dependencies(); ++j) {
      size_t idep = task(i).dependency(j);
      next[idep].push_back(i);
    }
  }

  // heap of pairs (task_id, priority)
  std::priority_queue<std::pair<size_t, int>,
                      std::vector<std::pair<size_t, int>>,
                      PriorityComp> queue;
  for (size_t i = 0; i < size(); ++i) {
    if (task(i).num_dependencies() == 0) {
      queue.push(std::make_pair(i, priority_[i]));
    }
  }
  size_t res_count = project_->num_resources();

  // availability time for resource_
  std::vector<int> time(res_count, 1);

  // number of complete dependencies for tasks
  std::vector<size_t> dep_count(size());

  while (!queue.empty()) {
    // take next task
    size_t itask = queue.top().first;
    queue.pop();

    // find max finish time of all dependencies
    size_t res_idx = resource_idx(itask);
    int min_start = 1;
    for (size_t i = 0; i < task(itask).num_dependencies(); ++i) {
      size_t idep = task(itask).dependency(i);
      int fin = finish_time(idep) + 1;
      if (min_start < fin)
        min_start = fin;
    }

    // update start time for the task
    set_start(itask, std::max(min_start, time[res_idx]));
    // update availability time for resource
    time[res_idx] = finish_time(itask) + 1;

    // add all unblocked dependent tasks to the queue
    for (size_t i = 0; i < next[itask].size(); ++i) {
      size_t inext = next[itask][i];
      dep_count[inext]++;
      if (dep_count[inext] == task(inext).num_dependencies()) {
        queue.push(std::make_pair(inext, priority_[inext]));
      }
    }
  }
}

int PrioSchedule::ComputeDuration() {
  FixAll();

  int duration = -1;
  for (size_t i = 0; i < size(); i++) {
    int finish = finish_time(i);
    if (duration < finish)
      duration = finish;
  }

  std::fill(business_.begin(), business_.end(), 0);
  for (size_t i = 0; i < size(); i++) {
    size_t res_idx = resource_idx(i);
    business_[res_idx] += task(i).duration();
  }

  return duration;
}

void PrioSchedule::Reset() {
  Schedule::Reset();
  for (size_t i = 0; i < size(); i++) {
    priority_[i] = Util::Random::randint() % 5;
  }
}

};  // namespace SchedulingProblem
