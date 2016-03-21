#include "../include/Random.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <random>

bool Random::_seed = false;

bool Random::rand(double prob) {
//    double ans = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    double ans = ((double) ::rand() / (double) RAND_MAX);
//    printf(">> ans = %.5lf\n", ans);
    return ans < prob;
}

void Random::seed() {
    if (!_seed) {
        printf("SEEEEEEEEEEEEEEEEEEEED!!!!!!!!!!!!!!!11111111\n");
        _seed = true;
        srand(time(0));
    }
}

int Random::randint() {
    seed();
    return ::rand();
}
