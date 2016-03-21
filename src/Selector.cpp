#include "../include/Selector.h"
#include "../include/Random.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Schedule* Selector::select(Population *p) {
    // select n random genotypes

    int p_size = p->size();
    for (int i = 0; i < n; i++) {
        int idx = Random::randint() % (p_size - i) + i;
        std::swap(p->genotype[i], p->genotype[idx]);
    }

    // find solution with max fitness
    int min_idx = 0;
    int min_fitness = p->genotype[0]->fitness();
    for (int i = 1; i < n; i++) {
        int i_fitness = p->genotype[i]->fitness();
//        printf("FIT: %d\n", i_fitness);
        if (i_fitness < min_fitness) {
            min_idx = i;
            min_fitness = i_fitness;
        }
    }

    return p->genotype[min_idx];
}
