#include "../include/Task.h"

Task::~Task() {
  delete[] res;
  delete[] dep;
  delete[] next;
}

int Task::res_size() {
  return nres;
}

int Task::dep_size() {
  return ndep;
}
