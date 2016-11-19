#include "../include/Schedule.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <utility>

#include "../include/Project.h"

namespace SchedulingProblem {

int Schedule::Fitness() {
  if (fitness_ == -1) {
    fitness_ = ComputeFitness();
  }
  return fitness_;
}

void Schedule::PrintState(bool is_short) {
  if (!is_short) {
    for (size_t i = 0; i < size_; i++)
      std::cout << "Task ID: " << task(i).id()
                << ", Resource ID: " << resource(i)
                << ", start time: " << start_[i] << "\n";
  }
  std::cout << "Fitness (finish): " << Fitness() << "\n";
}

Schedule::~Schedule() {}

};  // namespace SchedulingProblem
