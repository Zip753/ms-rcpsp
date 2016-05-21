//
// Created by ivan on 26.04.16.
//

#include "../include/OnePointCrossover.h"
#include "../include/Random.h"

Schedule *OnePointCrossover::cross(std::pair<Schedule *, Schedule *> p) {
    Schedule *s = new Schedule(p.first);

    int n = s->size();
    int idx = Random::randint() % n;
    for (int i = idx; i < n; i++)
        s->ires[i] = p.second->ires[i];

    return s;
}
