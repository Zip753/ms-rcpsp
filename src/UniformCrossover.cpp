//
// Created by ivan on 24.04.16.
//

#include "../include/UniformCrossover.h"
#include "../include/Random.h"

Schedule *UniformCrossover::cross(std::pair<Schedule *, Schedule *> p) {
    Schedule *s = new Schedule(p.first);

    int n = s->size();
    for (int i = 0; i < n; i++) {
        if (Random::randint() % 2 == 1) {
            s->ires[i] = p.second->ires[i];
        }
    }

    return s;
}

