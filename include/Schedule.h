#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Task.h"
#include <utility>
#include <cstdio>
#include <set>

class Schedule {
public:
    Schedule();
    Schedule(int *_ires);
    Schedule(Schedule *s);
    ~Schedule();

    int fitness();
    void show(bool sh = false);
    void show(FILE *stream);
    int size();

    int *ires; // own
    int *start; // own
    int *business; // own
    int max_res_count(int i);
    int resource(int i);
    bool eq(Schedule *s);
private:
    int n;
    Task** tasks; // reference
    int _fitness = -1;

    bool *visited;

    void init(bool create_ires); // constructor hook
    void update_start(int i);
    void reschedule();
    void fix_all();
    int finish_time(int i);
};

#endif // SCHEDULE_H
