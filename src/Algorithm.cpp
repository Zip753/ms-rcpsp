#include "../include/Algorithm.h"

Schedule* Algorithm::solve(FILE* stat) {
    if (steps == -1) {
        return 0;
    }
    for (int step = 0; step < steps; step++) {
        // evaluation
        update_best();
        // patrial results
        if (step % 1 == 0) {
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
                addToPopulation(next_pop, i, a_mut);
                // clear memory
                delete a_cross;
            } else {
                addToPopulation(next_pop, i, mutator->mutate(a));
                addToPopulation(next_pop, i, mutator->mutate(b));
            }
        }
        delete population;
        population = new Population(n, next_pop);
    }
    update_best();
    return global_best;
}

void Algorithm::update_best() {
    best = new Schedule(population->best());
    if (global_best == nullptr) {
        global_best = best;
    } else if (global_best->fitness() > best->fitness()) {
        global_best = best;
    }
}

void Algorithm::addToPopulation(Schedule **pop, int &idx, Schedule *sample) {
    if (remove_clones) {
        for (int k = 0; k < 3; k++) {
            bool contains = false;
            for (int i = 0; i < idx; i++)
                if (pop[i]->eq(sample)) {
                    contains = true;
                    break;
                }
            if (contains) {
                mutator->force_mutate(sample);
            } else {
                pop[idx++] = sample;
                return;
            }
        }
        pop[idx++] = new Schedule();
    } else {
        pop[idx++] = sample;
    }
}

Schedule* Algorithm::solve() {
    return solve(0);
}
