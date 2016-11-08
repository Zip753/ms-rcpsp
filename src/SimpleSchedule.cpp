#include "../include/SimpleSchedule.h"

#include <algorithm>

#include "../include/Project.h"
#include "../include/Random.h"

namespace SchedulingProblem {

bool SimpleSchedule::operator==(const SimpleSchedule& s) const {
  if (n != s.size()) return false;
  for (int i = 0; i < n; i++)
    if (ires[i] != s.ires[i])
      return false;
  return true;
}

void SimpleSchedule::init(bool create_ires) {
  if (create_ires) {
    ires = std::vector<int>(n, 0);
    reset();
  }

  visited = std::vector<bool>(n);

  int rcount = Project::get_res_count();
  business = std::vector<int>(rcount);
}

SimpleSchedule::SimpleSchedule() : Schedule() {
  init(true);
}

SimpleSchedule::SimpleSchedule(const SimpleSchedule& s) : Schedule() {
  init(false);
  ires = std::vector<int>(n, 0);
  for (int i = 0; i < n; i++) {
    ires[i] = s.ires[i];
  }
}

SimpleSchedule::SimpleSchedule(std::vector<int> _ires) : Schedule(_ires) {
  init(false);
}

void SimpleSchedule::update_start(int i) {
  if (!visited[i]) {
    visited[i] = true;
    for (int j = 0; j < task(i).num_dependencies(); j++) {
      int prev = task(i).dependency(j);
      update_start(prev);
      int finish = finish_time(prev);
      if (start[i] < finish)
        start[i] = finish;
    }
  }
}

void SimpleSchedule::reschedule() {
  // first, set earliest start (from fin)
  visited = std::vector<bool>(n, false);
  for (int i = 0; i < n; ++i) {
    update_start(i);
  }
}

void SimpleSchedule::fix_all() {
  reschedule();

  bool* used = new bool[n];
  std::fill_n(used, n, false);

  for (int i = 0; i < n; i++) {
    // select task with earliest start
    int min_start_idx = -1;
    for (int j = 0; j < n; j++)
      if (!used[j]) {
        if (min_start_idx == -1 || start[j] < start[min_start_idx])
          min_start_idx = j;
      }
    used[min_start_idx] = true;
    // select all tasks with same resource and shift them
    int res = resource(min_start_idx);
    bool is_conflict = false;
    int finish = finish_time(min_start_idx);
    for (int j = 0; j < n; j++)
      if (!used[j] && resource(j) == res && start[j] < finish) {
        start[j] = finish;
        is_conflict = true;
      }
    // reschedule if anything changed
    if (is_conflict)
      reschedule();
  }

  delete[] used;
}

int SimpleSchedule::compute_fitness() {
  fix_all();

  for (int i = 0; i < n; i++) {
    int finish = finish_time(i);
    if (_fitness < finish)
      _fitness = finish;
  }

  std::fill(business.begin(), business.end(), 0);
  for (int i = 0; i < n; i++) {
    int res = resource(i);
    business[res] += task(i).duration();
  }

  return _fitness;
}

void SimpleSchedule::reset() {
  for (int i = 0; i < n; i++) {
    ires[i] = Util::Random::randint() % Project::task(i).num_resources();
  }
}

};  // namespace SchedulingProblem
