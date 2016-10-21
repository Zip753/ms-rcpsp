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
  for (int i = 0; i < n; i++)
    if (ires[i] != s.ires[i] || prio[i] != s.prio[i])
      return false;
  return true;
}

void PrioSchedule::init(bool initialize) {
  if (initialize) {
    ires = std::vector<int>(n, 0);
    prio = std::vector<int>(n, 0);
    reset();
  }

  business = std::vector<int>(Project::get_res_count());
}

PrioSchedule::PrioSchedule() : Schedule() {
  init(true);
}

PrioSchedule::PrioSchedule(PrioSchedule* s) : Schedule() {
  init(false);
  ires = std::vector<int>(n, 0);
  prio = std::vector<int>(n, 0);
  for (int i = 0; i < n; i++) {
    ires[i] = s->ires[i];
    prio[i] = s->prio[i];
  }
}

PrioSchedule::PrioSchedule(std::vector<int> _ires, std::vector<int> _prio)
    : Schedule(_ires), prio(_prio) {
  init(false);
}

void PrioSchedule::fix_all() {
  struct PriorityComp {
    bool operator()(const std::pair<int, int> a,
                    const std::pair<int, int> b) const {
      return a.second < b.second;
    }
  };

  // heap of pairs (task_id, priority)
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      PriorityComp> queue;
  for (int i = 0; i < n; ++i) {
    if (task(i).num_dependencies() == 0) {
      queue.push(std::make_pair(i, prio[i]));
    }
  }
  int res_count = Project::get_res_count();

  // availability time for resource_
  std::vector<int> time = std::vector<int>(res_count);

  // number of complete dependency_ for tasks
  std::vector<int> dep_count = std::vector<int>(n);

  while (!queue.empty()) {
    // take next task
    int itask = queue.top().first;
    queue.pop();

    // find max finish time of all dependency_
    int res_idx = resource(itask);
    int min_start = 0;
    for (int i = 0; i < task(itask).num_dependencies(); ++i) {
      int idep = task(itask).dependency(i);
      int fin = finish_time(idep);
      if (min_start < fin)
        min_start = fin;
    }

    // update start time for the task
    start[itask] = std::max(min_start, time[res_idx]);
    // update availability time for resource
    time[res_idx] = finish_time(itask);

    // add all unblocked dependent tasks to the queue
    for (int i = 0; i < task(itask).next.size(); ++i) {
      int inext = task(itask).next[i];
      dep_count[inext]++;
      if (dep_count[inext] == task(inext).num_dependencies()) {
        queue.push(std::make_pair(inext, prio[inext]));
      }
    }
  }
}

int PrioSchedule::compute_fitness() {
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

void PrioSchedule::reset() {
  for (int i = 0; i < n; i++) {
    ires[i] = Util::Random::randint() % Project::task(i).num_resources();
    prio[i] = i;
  }
  std::random_shuffle(prio.begin(), prio.end());
}

};  // namespace SchedulingProblem
