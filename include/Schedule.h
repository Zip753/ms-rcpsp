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
    void show();
    void show(FILE *stream);
    int size();

    int *ires; // assignment of resources to tasks
    int max_res_count(int i);
private:
    int n;
    Task** tasks; // copies of tasks with new dependencies
    Task *st, *fin;
    int _fitness = -1;

    void init(); // constructor hook

    void update_start(int i);
    void update_finish(int i);
    void reschedule();
    std::pair<int, int> check_conflict();
    std::set<int> checked_res;

    struct Comparator {
        Comparator(Task **_tasks) : tasks(_tasks) {}
        bool operator()(const int& i, const int& j) {
            return tasks[i]->start < tasks[j]->start;
        }
        Task **tasks;
    };
};

#endif // SCHEDULE_H
