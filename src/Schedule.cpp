#include "../include/Schedule.h"
#include "../include/Project.h"
#include "../include/Random.h"
#include <cstdio>
#include <map>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

void Schedule::init() {
    Project* proj = Project::get();
    n = proj->size();
    ires = new int[n];
    for (int i = 0; i < n; i++)
        ires[i] = Random::randint() % proj->tasks[i]->res_size();

    tasks = new Task*[n + 1];
    for (int i = 0; i < n; i++)
        tasks[i] = new Task(proj->tasks[i]);

    fin = tasks[n] = new Task(-1, 0, 0, 0, 0, 0);

    // add reverse connections
    for (int i = 0; i < n; i++) {
        for (auto it = tasks[i]->dep.begin(); it != tasks[i]->dep.end(); it++) {
            int to = *it;
            tasks[to]->next.push_back(i);
        }
    }

    // connect everything to last task
    for (int i = 0; i < n; i++)
        if (tasks[i]->next.empty()) {
            tasks[i]->next.push_back(n + 1);
            fin->dep.push_back(i);
        }
}

Schedule::Schedule() {
    init();
}

Schedule::Schedule(Schedule *s) {
    init();
    for (int i = 0; i < n; i++)
        ires[i] = s->ires[i];
}

Schedule::~Schedule() {
    for (int i = 0; i < n; i++)
        delete tasks[i];
    delete[] tasks;
    delete[] ires;
}

void Schedule::update_start(int i) {
    for (auto it = tasks[i]->dep.begin(); it != tasks[i]->dep.end(); it++) {
        int prev = *it;
        update_start(prev);
    }
    if (!tasks[i]->dep.empty()) {
        for (auto it = tasks[i]->dep.begin(); it != tasks[i]->dep.end(); it++) {
            int prev = *it;
            int finish = tasks[prev]->start + tasks[prev]->duration;
            if (tasks[i]->start < finish)
                tasks[i]->start = finish;
        }
    }
}

void Schedule::reschedule() {
    // first, set earliest start (from fin)
    update_start(n);
}

void Schedule::fix_all() {
    reschedule();
    bool *used = new bool[n];
    for (int i = 0; i < n; i++)
        used[i] = false;
//    for (int j = 0; j < n; j++)
//        printf("%d => %d\n", tasks[j]->id, tasks[j]->start);
    for (int i = 0; i < n; i++) {
        // select task with earliest start
        int min_start_idx = -1;
        for (int j = 0; j < n; j++)
            if (!used[j]) {
                if (min_start_idx == -1)
                    min_start_idx = j;
                else if (tasks[j]->start < tasks[min_start_idx]->start)
                    min_start_idx = j;
            }
        used[min_start_idx] = true;
        // select all tasks with same resource and shift them
        int res = tasks[min_start_idx]->res[ires[min_start_idx]];
        bool is_conflict = false;
        int finish = tasks[min_start_idx]->start + tasks[min_start_idx]->duration;
        for (int j = 0; j < n; j++)
            if (!used[j] && tasks[j]->res[ires[j]] == res && tasks[j]->start < finish) {
                tasks[j]->start = finish;
                is_conflict = true;
            }
        // reschedule if anything changed
        if (is_conflict)
            reschedule();
    }
}

int Schedule::fitness() {
    if (_fitness == -1) {
        fix_all();
        _fitness = fin->start;
    }
    return _fitness;
}

int Schedule::size() {
    return n;
}

int Schedule::max_res_count(int i) {
    return tasks[i]->res_size();
}

void Schedule::show(bool sh) {
    if (!sh) {
        for (int i = 0; i < n; i++)
            printf("Task ID: %d, Resource ID: %d, start time: %d\n",
                tasks[i]->id, tasks[i]->res[ires[i]], tasks[i]->start);
    }
    printf("fitness (finish): %d\n", fitness());
}

void Schedule::show(FILE *stream) {
    fprintf(stream, "Hour 	 Resource assignments (resource ID - task ID) \n");
    std::map<int, std::list<std::pair<int, int> > > timeline;
    for (int i = 0; i < n; i++) {
        int start = tasks[i]->start + 1;
        int res = tasks[i]->res[ires[i]];
        int task_id = tasks[i]->id;

        if (timeline.count(start) == 0)
            timeline[start] = std::list<std::pair<int, int> >();
        timeline[start].push_back(std::make_pair(res, task_id));
    }
    for (auto it = timeline.begin(); it != timeline.end(); it++) {
        fprintf(stream, "%d ", it->first);
        for (auto lit = it->second.begin(); lit != it->second.end(); lit++) {
            fprintf(stream, "%d-%d ", lit->first, lit->second);
        }
        fprintf(stream, "\n");
    }
}
