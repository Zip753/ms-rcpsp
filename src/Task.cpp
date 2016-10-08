#include "../include/Task.h"

Task::~Task() {
  delete[] res;
  delete[] dep;
  delete[] next;
}
