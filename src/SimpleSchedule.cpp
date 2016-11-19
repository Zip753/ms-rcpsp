#include "../include/SimpleSchedule.h"

#include <algorithm>
#include <vector>

#include "../include/Project.h"
#include "../include/Random.h"

namespace SchedulingProblem {

bool SimpleSchedule::operator==(const SimpleSchedule& s) const {
  if (size_ != s.size()) return false;
  for (size_t i = 0; i < size_; i++)
    if (resource_idx_[i] != s.resource_idx_[i])
      return false;
  return true;
}

void SimpleSchedule::init(bool create_ires) {
  if (create_ires) {
    resource_idx_ = std::vector<size_t>(size_, 0);
    reset();
  }

  visited = std::vector<bool>(size_);

  size_t rcount = project_->num_resources();
  business = std::vector<int>(rcount);
}

SimpleSchedule::SimpleSchedule(Project* project_) : Schedule(project_) {
  init(true);
}

SimpleSchedule::SimpleSchedule(const SimpleSchedule& s) : Schedule(s.project_) {
  init(false);
  resource_idx_ = std::vector<size_t>(size_, 0);
  for (size_t i = 0; i < size_; i++) {
    resource_idx_[i] = s.resource_idx_[i];
  }
}

void SimpleSchedule::update_start(size_t i) {
  if (!visited[i]) {
    visited[i] = true;
    for (size_t j = 0; j < task(i).num_dependencies(); j++) {
      size_t prev = task(i).dependency(j);
      update_start(prev);
      int finish = finish_time(prev);
      if (start_[i] < finish)
        start_[i] = finish;
    }
  }
}

void SimpleSchedule::reschedule() {
  // first, set earliest start (from fin)
  visited = std::vector<bool>(size_, false);
  for (size_t i = 0; i < size_; ++i) {
    update_start(i);
  }
}

void SimpleSchedule::fix_all() {
  reschedule();

  std::vector<bool> used(size_, false);

  for (size_t i = 0; i < size_; i++) {
    // select task with earliest start
    bool first = true;
    size_t min_start_idx = 0;
    for (size_t j = 0; j < size_; j++)
      if (!used[j]) {
        if (first || start_[j] < start_[min_start_idx]) {
          first = false;
          min_start_idx = j;
        }
      }
    used[min_start_idx] = true;
    // select all tasks with same resource and shift them
    size_t res = resource(min_start_idx);
    bool is_conflict = false;
    int finish = finish_time(min_start_idx);
    for (size_t j = 0; j < size_; j++)
      if (!used[j] && resource(j) == res && start_[j] < finish) {
        start_[j] = finish;
        is_conflict = true;
      }
    // reschedule if anything changed
    if (is_conflict)
      reschedule();
  }
}

int SimpleSchedule::ComputeFitness() {
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

void SimpleSchedule::reset() {
  for (size_t i = 0; i < size_; i++) {
    resource_idx_[i] =
        Util::Random::randint() % project_->task(i).num_resources();
  }
}

};  // namespace SchedulingProblem
