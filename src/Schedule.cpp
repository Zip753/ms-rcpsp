#include "../include/Schedule.h"

#include <list>
#include <map>
#include <vector>
#include <utility>

#include "../include/Project.h"

namespace SchedulingProblem {

int Schedule::fitness() {
  if (_fitness == -1) {
    _fitness = compute_fitness();
  }
  return _fitness;
}

void Schedule::printState(bool is_short) {
  if (!is_short) {
    for (int i = 0; i < n; i++)
      printf("Task ID: %d, Resource ID: %d, start time: %d\n",
             task(i).id, resource(i), start[i]);
  }
  printf("fitness (finish): %d\n", fitness());
}

void Schedule::writeToFile(FILE* stream) {
  fprintf(stream, "Hour 	 Resource assignments (resource ID - task ID) \n");
  std::map<int, std::list<std::pair<int, int> > > timeline;
  for (int i = 0; i < n; i++) {
    int st = start[i] + 1;
    int res = Project::get_res_id(resource(i));
    int task_id = task(i).id;

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

Schedule::Schedule() : start(std::vector<int>(Project::size(), 0)),
                       n(Project::size()) {}

Schedule::~Schedule() {}

};  // namespace SchedulingProblem
