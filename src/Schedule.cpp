#include "../include/Schedule.h"

#include <fstream>
#include <iostream>
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

void Schedule::PrintState(bool is_short) {
  if (!is_short) {
    for (size_t i = 0; i < n; i++)
      std::cout << "Task ID: " << task(i).id()
                << ", Resource ID: " << resource(i)
                << ", start time: " << start[i] << "\n";
  }
  std::cout << "fitness (finish): " << fitness() << "\n";
}

void Schedule::Write(std::ostream &stream) {
  stream << "Hour \t Resource assignments (resource ID - task ID) \n";
  std::map<int, std::list<std::pair<int, int> > > timeline;
  for (size_t i = 0; i < n; i++) {
    int st = start[i] + 1;
    int res = project_->resource_id(resource(i));
    int task_id = task(i).id();

    if (timeline.count(st) == 0) {
      timeline[st] = std::list<std::pair<int, int> >();
    }
    timeline[st].push_back(std::make_pair(res, task_id));
  }
  for (auto it = timeline.begin(); it != timeline.end(); it++) {
    stream << it->first << " ";
    for (auto lit = it->second.begin(); lit != it->second.end(); lit++) {
      stream << lit->first << "-" << lit->second;
    }
    stream << std::endl;
  }
}

Schedule::~Schedule() {}

};  // namespace SchedulingProblem
