//
// Created by ivan on 24.04.16.
//

#include <algorithm>
#include "../include/UniformCrossover.h"
#include "../include/Random.h"

bool comp(std::pair<int, int> a, std::pair<int, int> b) {
    return a.second < b.second;
}

Schedule *UniformCrossover::cross(std::pair<Schedule *, Schedule *> p) {
    Schedule *s = new Schedule(p.first);

    int n = s->size();
    for (int i = 0; i < n; i++) {
        if (Random::randint() % 2 == 1) {
            s->ires[i] = p.second->ires[i];
        }

        if (Random::randint() % 2 == 1) {
            s->prio[i] = p.second->prio[i];
        }
    }

    std::pair<int, int> *idx = new std::pair<int, int>[n];

    for (int i = 0; i < n; ++i) {
        idx[i] = std::make_pair(i, s->prio[i]);
    }

    std::sort(idx, idx + n, comp);

    for (int i = 0; i < n; ++i) {
        s->prio[idx[i].first] = i;
    }

    delete[] idx;

    return s;
}
