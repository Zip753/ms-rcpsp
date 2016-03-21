#include "../include/Crossover.h"
#include "../include/Random.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

std::pair<Schedule*, Schedule*> Crossover::cross(std::pair<Schedule*, Schedule*> p) {
    Schedule *a = new Schedule(p.first),
            *b = new Schedule(p.second);
    if (Random::rand(p_cross)) {
        int n = p.first->size();
        for (int i = 0; i < n; i++) {
            if (Random::randint() & 1) {
                std::swap(a->ires[i], b->ires[i]);
            }
        }
    }
    return std::make_pair(a, b);
}
