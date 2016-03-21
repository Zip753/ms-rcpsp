#include "../include/Algorithm.h"
#include <utility>
#include <cstdio>

Schedule* Algorithm::solve(FILE *stream) {
    if (steps == -1) {
        return 0;
    }
    for (int step = 0; step < steps; step++) {
        // evaluation
        best = population->best();
        if (step % 1 == 0) {
            printf("step == %d\n", step);
            printf("best: ");
            best->show();
            if (stream != 0) {
                best->show(stream);
            }
        }
        // move to next generation
        Schedule** next_pop = new Schedule*[population->size()];
        int n = population->size();
        for (int i = 0; i < n; i += 2) {
            // selection
            Schedule *a = selector->select(population);
            Schedule *b = selector->select(population);
            while (b == a) {
                b = selector->select(population);
            }
            // create new Solution instances
            a = new Schedule(a);
            b = new Schedule(b);
            // crossover
            std::pair<Schedule*, Schedule*> samples = std::make_pair(a, b);
            samples = crossover->cross(samples);
            a = samples.first;
            b = samples.second;
            // mutation
            a = mutator->mutate(a);
            b = mutator->mutate(b);
            // add to next generation
            next_pop[i] = a;
            next_pop[i + 1] = b;
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
