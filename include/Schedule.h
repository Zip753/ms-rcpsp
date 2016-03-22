#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Task.h"
#include <utility>
#include <cstdio>
#include <set>

class Schedule {
public:
    Schedule();
    Schedule(Schedule *s);
    ~Schedule();

    int fitness();
    void show(bool sh = false);
    void show(FILE *stream);
    int size();

    int *ires; // assignment of resources to tasks
    int max_res_count(int i);
private:
    int n;
    Task** tasks; // copies of tasks with new dependencies
    Task *fin;
    int _fitness = -1;

    void init(); // constructor hook

    void update_start(int i);
    void reschedule();
    void fix_all();
    bool fix_conflict(int idx);
    void sort_by_start();
};

#endif // SCHEDULE_H
