#include "../include/PrioSchedule.h"

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "../include/Project.h"
#include "../include/Random.h"

namespace SchedulingProblem {

bool PrioSchedule::operator==(PrioSchedule s) const {
  if (n != s.size()) return false;
  for (size_t i = 0; i < n; i++)
    if (ires[i] != s.ires[i] || prio[i] != s.prio[i])
      return false;
  return true;
}

void PrioSchedule::init(bool initialize) {
  if (initialize) {
    ires = std::vector<size_t>(n, 0);
    prio = std::vector<int>(n, 0);
    reset();
  }

  business = std::vector<int>(project_->num_resources());
}

PrioSchedule::PrioSchedule(Project* project_) : Schedule(project_) {
  init(true);
}

PrioSchedule::PrioSchedule(const PrioSchedule& s) : Schedule(s.project_) {
  init(false);
  ires = std::vector<size_t>(n, 0);
  prio = std::vector<int>(n, 0);
  for (size_t i = 0; i < n; i++) {
    ires[i] = s.ires[i];
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

  // heap of pairs (task_id, priority)
  std::priority_queue<std::pair<size_t, int>,
                      std::vector<std::pair<size_t, int>>,
                      PriorityComp> queue;
  for (size_t i = 0; i < n; ++i) {
    if (task(i).num_dependencies() == 0) {
      queue.push(std::make_pair(i, prio[i]));
    }
  }
  size_t res_count = project_->num_resources();

  // availability time for resource_
  std::vector<int> time(res_count);

  // number of complete dependency_ for tasks
  std::vector<size_t> dep_count(n);

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
    start[itask] = std::max(min_start, time[res_idx]);
    // update availability time for resource
    time[res_idx] = finish_time(itask);

    // add all unblocked dependent tasks to the queue
    for (size_t i = 0; i < task(itask).next.size(); ++i) {
      size_t inext = task(itask).next[i];
      dep_count[inext]++;
      if (dep_count[inext] == task(inext).num_dependencies()) {
        queue.push(std::make_pair(inext, prio[inext]));
      }
    }
  }
}

int PrioSchedule::compute_fitness() {
  fix_all();

  for (size_t i = 0; i < n; i++) {
    int finish = finish_time(i);
    if (_fitness < finish)
      _fitness = finish;
  }

  std::fill(business.begin(), business.end(), 0);
  for (size_t i = 0; i < n; i++) {
    size_t res = resource(i);
    business[res] += task(i).duration();
  }

  return _fitness;
}

void PrioSchedule::reset() {
  for (size_t i = 0; i < n; i++) {
    ires[i] = Util::Random::randint() % project_->task(i).num_resources();
    prio[i] = (int)i;
  }
  std::random_shuffle(prio.begin(), prio.end());
}

};  // namespace SchedulingProblem
