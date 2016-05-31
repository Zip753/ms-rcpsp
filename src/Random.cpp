#include "../include/Random.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <random>
#include <zconf.h>

bool Random::_seed = false;

bool Random::rand(double prob) {
//    double ans = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    double ans = ((double) ::rand() / (double) RAND_MAX);
//    printf(">> ans = %.5lf\n", ans);
    return ans < prob;
}

// http://www.concentric.net/~Ttwang/tech/inthash.htm
unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

void Random::seed() {
    if (!_seed) {
//        printf("SEEEEEEEEEEEEEEEEEEEED!!!!!!!!!!!!!!!11111111\n");
        _seed = true;
        unsigned long seed = mix(clock(), time(NULL), getpid());
        srand(seed);
    }
}

int Random::randint() {
    seed();
    return ::rand();
}
