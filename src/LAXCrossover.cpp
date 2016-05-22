#include "../include/LAXCrossover.h"
#include "../include/Project.h"
#include <cstdlib>
#include <algorithm>

bool lax_comp(std::pair<int, int> a, std::pair<int, int> b) {
    return a.second < b.second;
}

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

    std::pair<int, int> *idx = new std::pair<int, int>[n];
    int *prio = new int[n];

    for (int i = 0; i < n; ++i) {
        idx[i] = std::make_pair(i, prio[i]);
    }

    std::sort(idx, idx + n, lax_comp);

    for (int i = 0; i < n; ++i) {
        prio[idx[i].first] = i;
    }

    delete[] idx;

    return new Schedule(ires, prio);
}


