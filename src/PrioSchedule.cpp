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
  for (size_t i = 0; i < size_; i++)
    if (priority_[i] != other.priority_[i])
      return false;
  return true;
}

void PrioSchedule::Init(bool initialize) {
  if (initialize) {
    capable_resource_idx_ = std::vector<size_t>(size_, 0);
    priority_ = std::vector<int>(size_, 0);
    Reset();
  }

  business_ = std::vector<int>(project_->num_resources());
}

PrioSchedule::PrioSchedule(Project* project_) : Schedule(project_) {
  Init(true);
}

PrioSchedule::PrioSchedule(const PrioSchedule& s) : Schedule(s.project_) {
  Init(false);
  capable_resource_idx_ = std::vector<size_t>(size_, 0);
  priority_ = std::vector<int>(size_, 0);
  for (size_t i = 0; i < size_; i++) {
    capable_resource_idx_[i] = s.capable_resource_idx_[i];
    priority_[i] = s.priority_[i];
  }
}

void PrioSchedule::FixAll() {
  struct PriorityComp {
    bool operator()(const std::pair<int, int> a,
                    const std::pair<int, int> b) const {
      return a.second < b.second;
    }
  };

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
  std::priority_queue<std::pair<size_t, int>,
                      std::vector<std::pair<size_t, int>>,
                      PriorityComp> queue;
  for (size_t i = 0; i < size_; ++i) {
    if (task(i).num_dependencies() == 0) {
      queue.push(std::make_pair(i, priority_[i]));
    }
  }
  size_t res_count = project_->num_resources();

  // availability time for resource_
  std::vector<int> time(res_count);

  // number of complete dependency_ for tasks
  std::vector<size_t> dep_count(size_);

  while (!queue.empty()) {
    // take next task
    size_t itask = queue.top().first;
    queue.pop();

    // find max finish time of all dependency_
    size_t res_idx = resource_idx(itask);
    int min_start = 0;
    for (size_t i = 0; i < task(itask).num_dependencies(); ++i) {
      size_t idep = task(itask).dependency(i);
      int fin = finish_time(idep);
      if (min_start < fin)
        min_start = fin;
    }

    // update start time for the task
    start_[itask] = std::max(min_start, time[res_idx]);
    // update availability time for resource
    time[res_idx] = finish_time(itask);

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

int PrioSchedule::ComputeFitness() {
  FixAll();

  for (size_t i = 0; i < size_; i++) {
    int finish = finish_time(i);
    if (fitness_ < finish)
      fitness_ = finish;
  }

  std::fill(business_.begin(), business_.end(), 0);
  for (size_t i = 0; i < size_; i++) {
    size_t res_idx = resource_idx(i);
    business_[res_idx] += task(i).duration();
  }

  return fitness_;
}

void PrioSchedule::Reset() {
  Schedule::Reset();
  for (size_t i = 0; i < size_; i++) {
    priority_[i] = Util::Random::randint() % static_cast<int>(size_);
  }
}

};  // namespace SchedulingProblem
