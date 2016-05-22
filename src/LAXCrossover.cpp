#include "../include/LAXCrossover.h"
#include "../include/Project.h"
#include <cstdlib>

Schedule* LAXCrossover::cross(std::pair<Schedule*, Schedule*> p) {
    Schedule *a = new Schedule(p.first),
            *b = new Schedule(p.second);

    Project* proj = Project::get();
    int n = p.first->size();
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
    return new Schedule(ires);
}

