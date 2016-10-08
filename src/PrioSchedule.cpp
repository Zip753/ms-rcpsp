#include "../include/PrioSchedule.h"

#include <algorithm>
#include <queue>
#include <vector>

#include "../include/Project.h"
#include "../include/Random.h"

void PrioSchedule::init(bool initialize) {
  if (initialize) {
    ires = new int[n];
    prio = new int[n];
    for (int i = 0; i < n; i++) {
      ires[i] = Random::randint() % Project::get()->tasks[i]->res_size();
      prio[i] = i;
    }
    std::random_shuffle(prio, prio + n);
  }

  visited = new bool[n];

  int rcount = Project::get()->get_res_count();
  business = new int[rcount];
}

PrioSchedule::PrioSchedule() : Schedule() {
  init(true);
}

PrioSchedule::PrioSchedule(PrioSchedule *s) : Schedule() {
  init(false);
  ires = new int[n];
  prio = new int[n];
  for (int i = 0; i < n; i++) {
    ires[i] = s->ires[i];
    prio[i] = s->prio[i];
  }
}

PrioSchedule::PrioSchedule(int* _ires, int* _prio)
    : Schedule(_ires), prio(_prio) {
  init(false);
}

PrioSchedule::~PrioSchedule() {
  delete[] ires;
  delete[] prio;
  delete[] start;
  delete[] visited;
  if (business != nullptr) delete[] business;
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
    if (tasks[i]->dep_size() == 0) {
      queue.push(std::make_pair(i, prio[i]));
    }
  }
  int res_count = Project::get()->get_res_count();

  // availability time for resources
  int *time = new int[res_count];
  std::fill_n(time, res_count, 0);

  // number of complete dependencies for tasks
  int *dep_count = new int[n];
  std::fill_n(dep_count, n, 0);

  while (!queue.empty()) {
    // take next task
    int itask = queue.top().first;
    queue.pop();

    // find max finish time of all dependencies
    int res_idx = resource(itask);
    int min_start = 0;
    for (int i = 0; i < tasks[itask]->dep_size(); ++i) {
      int idep = tasks[itask]->dep[i];
      int fin = finish_time(idep);
      if (min_start < fin)
        min_start = fin;
    }

    // update start time for the task
    start[itask] = std::max(min_start, time[res_idx]);
    // update availability time for resource
    time[res_idx] = finish_time(itask);

    // add all unblocked dependent tasks to the queue
    for (int i = 0; i < tasks[itask]->next_size; ++i) {
      int inext = tasks[itask]->next[i];
      dep_count[inext]++;
      if (dep_count[inext] == tasks[inext]->dep_size()) {
        queue.push(std::make_pair(inext, prio[inext]));
      }
    }
  }

  delete[] time;
  delete[] dep_count;
}

void PrioSchedule::compute_fitness() {
  fix_all();

  for (int i = 0; i < n; i++) {
    int finish = finish_time(i);
    if (_fitness < finish)
      _fitness = finish;
  }

  std::fill_n(business, Project::get()->get_res_count(), 0);
  for (int i = 0; i < n; i++) {
    int res = resource(i);
    business[res] += tasks[i]->duration;
  }
}
