#include "../include/SimpleSchedule.h"

#include <algorithm>

#include "../include/Project.h"
#include "../include/Random.h"

void SimpleSchedule::init(bool create_ires) {
  if (create_ires) {
    ires = new int[n];
    for (int i = 0; i < n; i++) {
      ires[i] = Random::randint() % Project::get()->tasks[i]->res_size();
    }
  }

  visited = new bool[n];

  int rcount = Project::get()->get_res_count();
  business = new int[rcount];
}

SimpleSchedule::SimpleSchedule() : Schedule() {
  init(true);
}

SimpleSchedule::SimpleSchedule(SimpleSchedule* s) : Schedule() {
  init(false);
  ires = new int[n];
  for (int i = 0; i < n; i++) {
    ires[i] = s->ires[i];
  }
}

SimpleSchedule::SimpleSchedule(int* _ires) : Schedule(_ires) {
  init(false);
}

SimpleSchedule::~SimpleSchedule() {
  delete[] ires;
  delete[] start;
  delete[] visited;
  if (business != nullptr) delete[] business;
}

void SimpleSchedule::update_start(int i) {
  if (!visited[i]) {
    visited[i] = true;
    for (int j = 0; j < tasks[i]->dep_size(); j++) {
      int prev = tasks[i]->dep[j];
      update_start(prev);
      int finish = finish_time(prev);
      if (start[i] < finish)
        start[i] = finish;
    }
  }
}

void SimpleSchedule::reschedule() {
  // first, set earliest start (from fin)
  std::fill_n(visited, n, false);
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

  std::fill_n(business, Project::get()->get_res_count(), 0);
  for (int i = 0; i < n; i++) {
    int res = resource(i);
    business[res] += tasks[i]->duration;
  }

  return _fitness;
}
