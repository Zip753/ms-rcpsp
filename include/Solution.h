#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"
#include <cstdio>

class Graph;
class Solution {
public:
    Solution();
    Solution(Solution *s);
    Solution(int max);
    ~Solution();
    int fitness();
    int size();
    int maxColors();
    void show();
    void show(FILE* stream);
    void showGraph();

    int *color;
private:
    int max;
    int _fitness = -1;
};

#endif // SOLUTION_H
