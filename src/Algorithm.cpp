#include "../include/Algorithm.h"
#include <utility>
#include <cstdio>

Schedule* Algorithm::solve(FILE* stat) {
    if (steps == -1) {
        return 0;
    }
    for (int step = 0; step < steps; step++) {
        // evaluation
        best = population->best();
        // patrial results
        if (step % 5 == 0) {
            // result to console
            printf("step == %d\n", step);
            printf("best: ");
            best->show(true);
            // stats to file
            if (stat != 0) {
                population->showStat(stat);
//                best->show(stream);
            }
        }
        // move to next generation
        int n = population->size();
        Schedule** next_pop = new Schedule*[n];
        for (int i = 0; i < n;) {
            // selection
            Schedule *a = selector->select(population);
            Schedule *b;
            do { b = selector->select(population); } while (b == a);
            // crossover
            if (i == n - 1 || crossover->should_cross()) {
                Schedule *a_cross = crossover->cross(std::make_pair(a, b));
                // mutation
                Schedule *a_mut = mutator->mutate(a_cross);
                // add to next generation
                next_pop[i++] = a_mut;
                // clear memory
                delete a_cross;
            } else {
                next_pop[i++] = mutator->mutate(a);
                next_pop[i++] = mutator->mutate(b);
            }
        }
        delete population;
        population = new Population(n, next_pop);
    }
    best = population->best();
    return best;
}

Schedule* Algorithm::solve() {
    return solve(0);
}
