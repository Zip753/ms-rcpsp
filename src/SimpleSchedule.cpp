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

void SimpleSchedule::Init(bool create_ires) {
  if (create_ires) {
    resource_idx_ = std::vector<size_t>(size_, 0);
    Reset();
  }

  size_t rcount = project_->num_resources();
  business_ = std::vector<int>(rcount);
}

SimpleSchedule::SimpleSchedule(Project* project_) : Schedule(project_) {
  Init(true);
}

SimpleSchedule::SimpleSchedule(const SimpleSchedule& s) : Schedule(s.project_) {
  Init(false);
  resource_idx_ = std::vector<size_t>(size_, 0);
  for (size_t i = 0; i < size_; i++) {
    resource_idx_[i] = s.resource_idx_[i];
  }
}

void SimpleSchedule::UpdateStart(size_t i, std::vector<bool> &visited) {
  if (!visited[i]) {
    visited[i] = true;
    for (size_t j = 0; j < task(i).num_dependencies(); j++) {
      size_t prev = task(i).dependency(j);
      UpdateStart(prev, visited);
      int finish = finish_time(prev);
      if (start_[i] < finish)
        start_[i] = finish;
    }
  }
}

void SimpleSchedule::Reschedule() {
  // first, set earliest start (from fin)
  std::vector<bool> visited(size_, false);
  for (size_t i = 0; i < size_; ++i) {
    UpdateStart(i, visited);
  }
}

void SimpleSchedule::FixAll() {
  Reschedule();

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
      Reschedule();
  }
}

int SimpleSchedule::ComputeFitness() {
  FixAll();

  for (size_t i = 0; i < size_; i++) {
    int finish = finish_time(i);
    if (fitness_ < finish)
      fitness_ = finish;
  }

  std::fill(business_.begin(), business_.end(), 0);
  for (size_t i = 0; i < size_; i++) {
    size_t res = resource(i);
    business_[res] += task(i).duration();
  }

  return fitness_;
}

void SimpleSchedule::Reset() {
  for (size_t i = 0; i < size_; i++) {
    resource_idx_[i] =
        Util::Random::randint() % project_->task(i).num_resources();
  }
}

};  // namespace SchedulingProblem
