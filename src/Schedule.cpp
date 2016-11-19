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

Schedule::~Schedule() {}

};  // namespace SchedulingProblem
