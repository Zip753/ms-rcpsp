#include "../include/Population.h"

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
