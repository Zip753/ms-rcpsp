#include "../include/Population.h"
#include <cmath>

Population::Population(int size) {
    n = size;
    // ensure that population size is even
    if (n % 2 == 1) n++;
    genotype = new Schedule*[n];
    for (int i = 0; i < n; i++)
        genotype[i] = new Schedule();
}

Population::~Population() {
    for (int i = 0; i < n; i++)
        delete genotype[i];
    delete[] genotype;
}

int Population::size() {
    return n;
}

Schedule* Population::best() {
    Schedule *ans = genotype[0];
    for (int i = 1; i < n; i++)
        if (genotype[i]->fitness() < ans->fitness())
            ans = genotype[i];
    return ans;
}

void Population::showStat(FILE *stream) {
    int best_val = best()->fitness();
    double mean = 0;
    for (int i = 0; i < n; i++)
        mean += genotype[i]->fitness();
    mean /= n;
    double std_dev = 0;
    for (int i = 0; i < n; i++) {
        double x = mean - genotype[i]->fitness();
        std_dev += x * x;
    }
    std_dev /= n;
    std_dev = sqrt(std_dev);

    fprintf(stream, "%d %.4lf %.4lf\n", best_val, mean, std_dev);
}
