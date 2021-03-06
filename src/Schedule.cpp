#include "../include/SimpleSchedule.h"
#include "../include/Schedule.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <utility>

#include "../include/Project.h"
#include "../include/Random.h"

namespace SchedulingProblem {

int Schedule::Fitness() {
  if (fitness_ == kInvalidFitness) {
    fitness_ = ComputeDuration();
  }
  return fitness_;
}

void Schedule::PrintState(bool is_short) {
  if (!is_short) {
    for (size_t i = 0; i < size_; i++)
      std::cout << "Task ID: " << task(i).id()
                << ", Resource ID: " << resource(i).id()
                << ", start time: " << start_[i] << "\n";
  }
  std::cout << "Fitness (time): " << Fitness()
            << ", cost: " << TotalCost() << "\n";
}

Schedule::~Schedule() {}

bool Schedule::operator==(const Schedule &other) const {
  if (size() != other.size()) return false;
  for (size_t i = 0; i < size_; i++)
    if (capable_resource_idx_[i] != other.capable_resource_idx_[i])
      return false;
  return true;
}

void Schedule::Reset() {
  for (size_t i = 0; i < size_; i++) {
    capable_resource_idx_[i] =
        Util::Random::randint() % project_->task(i).num_capable_resources();
  }
}

double Schedule::TotalCost() const {
  double total = 0;
  for (size_t i = 0; i < size_; ++i) {
    total += resource(i).salary() * task(i).duration();
  }
  return total;
}

};  // namespace SchedulingProblem
