#include "../include/Solution.h"
#include "../include/Random.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstdio>

Solution::Solution() {}

Solution::Solution(Solution *s) {
    this->max = s->max;
    int n = Graph::get()->size();
    color = new int[n];
    std::copy(s->color, s->color + n, this->color);
}

Solution::Solution(int max) {
    this->max = max;
    int n = Graph::get()->size();
    color = new int[n];

    for (int i = 0; i < n; i++)
        color[i] = Random::randint() % max;
}

Solution::~Solution() {
    delete[] color;
}

int Solution::size() {
    return Graph::get()->size();
}

int Solution::fitness() {
    if (_fitness == -1) {
        _fitness = Graph::get()->fitness(this);
    }
    return _fitness;
}

int Solution::maxColors() {
    return this->max;
}

void Solution::show() {
    int n = Graph::get()->size();
    for (int i = 0; i < n; i++) {
        printf("%d", color[i]);
        if (i < n)
            printf(", ");
        else
            printf("; ");
    }
    printf("fitness: %d\n", fitness());
}

void Solution::show(FILE* stream) {
    int n = Graph::get()->size();
    for (int i = 0; i < n; i++)
        fprintf(stream, "%d\n", color[i] + 1);
}

void Solution::showGraph() {
    Graph::get()->showWithColors(this);
}
