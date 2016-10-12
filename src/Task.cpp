#include "../include/Task.h"

namespace SchedulingProblem {

Task::~Task() {
  delete[] res;
  delete[] dep;
  delete[] next;
}

};  // namespace SchedulingProblem
