#include "../include/Schedule.h"

#include <list>
#include <map>
#include <utility>

#include "../include/Project.h"

bool Schedule::eq(Schedule* s) {
  if (n != s->size()) return false;
  for (int i = 0; i < n; i++)
    if (ires[i] != s->ires[i])
      return false;
  return true;
}

int Schedule::fitness() {
  if (_fitness == -1) {
    compute_fitness();
  }
  return _fitness;
}

void Schedule::printState(bool is_short) {
  if (!is_short) {
    for (int i = 0; i < n; i++)
      printf("Task ID: %d, Resource ID: %d, start time: %d\n",
             tasks[i]->id, resource(i), start[i]);
  }
  printf("fitness (finish): %d\n", fitness());
}

void Schedule::writeToFile(FILE* stream) {
  fprintf(stream, "Hour 	 Resource assignments (resource ID - task ID) \n");
  std::map<int, std::list<std::pair<int, int> > > timeline;
  Project* proj = Project::get();
  for (int i = 0; i < n; i++) {
    int st = start[i] + 1;
    int res = proj->get_res_id(resource(i));
    int task_id = tasks[i]->id;

    if (timeline.count(st) == 0) {
      timeline[st] = std::list<std::pair<int, int> >();
    }
    timeline[st].push_back(std::make_pair(res, task_id));
  }
  for (auto it = timeline.begin(); it != timeline.end(); it++) {
    fprintf(stream, "%d ", it->first);
    for (auto lit = it->second.begin(); lit != it->second.end(); lit++) {
      fprintf(stream, "%d-%d ", lit->first, lit->second);
    }
    fprintf(stream, "\n");
  }
}

Schedule::Schedule() {
  Project* proj = Project::get();
  n = proj->size();
  this->tasks = proj->tasks;

  start = new int[n];
  std::fill_n(start, n, 0);
}
