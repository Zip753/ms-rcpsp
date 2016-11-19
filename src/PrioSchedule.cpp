#include "../include/PrioSchedule.h"

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "../include/Project.h"
#include "../include/Random.h"

namespace SchedulingProblem {

bool PrioSchedule::operator==(PrioSchedule s) const {
  if (size_ != s.size()) return false;
  for (size_t i = 0; i < size_; i++)
    if (resource_idx_[i] != s.resource_idx_[i] || prio[i] != s.prio[i])
      return false;
  return true;
}

void PrioSchedule::init(bool initialize) {
  if (initialize) {
    resource_idx_ = std::vector<size_t>(size_, 0);
    prio = std::vector<int>(size_, 0);
    reset();
  }

  business = std::vector<int>(project_->num_resources());
}

PrioSchedule::PrioSchedule(Project* project_) : Schedule(project_) {
  init(true);
}

PrioSchedule::PrioSchedule(const PrioSchedule& s) : Schedule(s.project_) {
  init(false);
  resource_idx_ = std::vector<size_t>(size_, 0);
  prio = std::vector<int>(size_, 0);
  for (size_t i = 0; i < size_; i++) {
    resource_idx_[i] = s.resource_idx_[i];
    prio[i] = s.prio[i];
  }
}

void PrioSchedule::fix_all() {
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
      queue.push(std::make_pair(i, prio[i]));
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
    size_t res_idx = resource(itask);
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
        queue.push(std::make_pair(inext, prio[inext]));
      }
    }
  }
}

int PrioSchedule::ComputeFitness() {
  fix_all();

  for (size_t i = 0; i < size_; i++) {
    int finish = finish_time(i);
    if (fitness_ < finish)
      fitness_ = finish;
  }

  std::fill(business.begin(), business.end(), 0);
  for (size_t i = 0; i < size_; i++) {
    size_t res = resource(i);
    business[res] += task(i).duration();
  }

  return fitness_;
}

void PrioSchedule::reset() {
  for (size_t i = 0; i < size_; i++) {
    resource_idx_[i] =
        Util::Random::randint() % project_->task(i).num_resources();
    prio[i] = (int)i;
  }
  std::random_shuffle(prio.begin(), prio.end());
}

};  // namespace SchedulingProblem
