#include "../include/LAXCrossover.h"

#include "../include/PrioSchedule.h"
#include "../include/Project.h"
#include "../include/Random.h"
#include "../include/SimpleSchedule.h"

template<>
PrioSchedule* LAXCrossover<PrioSchedule>::cross(PrioSchedule *a,
                                                PrioSchedule *b) {
  Project *proj = Project::get();
  int n = a->size();
  int *ires = new int[n];
  int *prio = new int[n];
  for (int i = 0; i < n; i++) {
    int a_res = a->resource(i);
    int b_res = b->resource(i);
    if (a->business[a_res] < b->business[b_res]) {
      ires[i] = a->ires[i];
    } else if (a->business[a_res] > b->business[b_res]) {
      ires[i] = b->ires[i];
    } else {
      double a_sal = proj->get_salary(a_res);
      double b_sal = proj->get_salary(b_res);
      if (a_sal < b_sal)
        ires[i] = a->ires[i];
      else
        ires[i] = b->ires[i];
    }

    if (Random::randint() & 1) {
      prio[i] = a->prio[i];
    } else {
      prio[i] = b->prio[i];
    }
  }

  return new PrioSchedule(ires, prio);
}

template<>
SimpleSchedule* LAXCrossover<SimpleSchedule>::cross(SimpleSchedule *a,
                                                    SimpleSchedule *b) {

  Project* proj = Project::get();
  int n = a->size();
  int *ires = new int[n];
  for (int i = 0; i < n; i++) {
    int a_res = a->resource(i);
    int b_res = b->resource(i);
    if (a->business[a_res] < b->business[b_res]) {
      ires[i] = a->ires[i];
    } else if (a->business[a_res] > b->business[b_res]) {
      ires[i] = b->ires[i];
    } else {
      double a_sal = proj->get_salary(a_res);
      double b_sal = proj->get_salary(b_res);
      if (a_sal < b_sal)
        ires[i] = a->ires[i];
      else
        ires[i] = b->ires[i];
    }
  }
  return new SimpleSchedule(ires);
}
