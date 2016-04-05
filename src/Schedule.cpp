#include "../include/Schedule.h"
#include "../include/Project.h"
#include "../include/Random.h"
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

void Schedule::init(bool create_ires) {
    Project* proj = Project::get();
    n = proj->size();
    this->tasks = proj->tasks;

    if (create_ires) {
        ires = new int[n];
        for (int i = 0; i < n; i++) {
            ires[i] = Random::randint() % proj->tasks[i]->res_size();
        }
    }

    start = new int[n];
    std::fill_n(start, n, 0);

    visited = new bool[n];

    int rcount = Project::get()->get_res_count();
    business = new int[rcount];
}

Schedule::Schedule() {
    init(true);
}

Schedule::Schedule(Schedule *s) {
    init(false);
    ires = new int[n];
    for (int i = 0; i < n; i++) {
        ires[i] = s->ires[i];
    }
}

Schedule::Schedule(int *_ires) : ires(_ires) {
    init(false);
}

Schedule::~Schedule() {
    delete[] ires;
    delete[] start;
    delete[] visited;
}

void Schedule::update_start(int i) {
    if (!visited[i]) {
        visited[i] = true;
        for (int j = 0; j < tasks[i]->dep_size(); j++) {
            int prev = tasks[i]->dep[j];
            update_start(prev);
        }
        if (tasks[i]->dep_size() > 0) {
            for (int j = 0; j < tasks[i]->dep_size(); ++j) {
                int prev = tasks[i]->dep[j];
                int finish = finish_time(prev);
                if (start[i] < finish)
                    start[i] = finish;
            }
        }
    }
}

void Schedule::reschedule() {
    // first, set earliest start (from fin)
    std::fill_n(visited, n, 0);
    for (int i = 0; i < n; ++i) {
        update_start(i);
    }
}

void Schedule::fix_all() {
    reschedule();

    bool *used = new bool[n];
    std::fill_n(used, n, false);

    for (int i = 0; i < n; i++) {
        // select task with earliest start
        int min_start_idx = -1;
        for (int j = 0; j < n; j++)
            if (!used[j]) {
                if (min_start_idx == -1)
                    min_start_idx = j;
                else if (start[j] < start[min_start_idx])
                    min_start_idx = j;
            }
        used[min_start_idx] = true;
        // select all tasks with same resource and shift them
        int res = resource(min_start_idx);
        bool is_conflict = false;
        int finish = finish_time(min_start_idx);
        for (int j = 0; j < n; j++)
            if (!used[j] && resource(j) == res && start[j] < finish) {
                start[j] = finish;
                is_conflict = true;
            }
        // reschedule if anything changed
        if (is_conflict)
            reschedule();
    }
}

int Schedule::resource(int i) {
    return tasks[i]->res[ires[i]];
}

int Schedule::finish_time(int i) {
    return start[i] + tasks[i]->duration;
}

int Schedule::fitness() {
    if (_fitness == -1) {
        fix_all();

        for (int i = 0; i < n; i++)
            if (_fitness < finish_time(i))
                _fitness = finish_time(i);

        std::fill_n(business, Project::get()->get_res_count(), 0);
        for (int i = 0; i < n; i++) {
            int res = resource(i);
            business[res]++;
        }
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
                tasks[i]->id, resource(i), start[i]);
    }
    printf("fitness (finish): %d\n", fitness());
}

void Schedule::show(FILE *stream) {
    fprintf(stream, "Hour 	 Resource assignments (resource ID - task ID) \n");
    std::map<int, std::list<std::pair<int, int> > > timeline;
    Project *proj = Project::get();
    for (int i = 0; i < n; i++) {
        int st = start[i] + 1;
        int res = proj->get_res_id(resource(i));
        int task_id = tasks[i]->id;

        if (timeline.count(st) == 0)
            timeline[st] = std::list<std::pair<int, int> >();
        timeline[st].push_back(std::make_pair(res, task_id));
    }
    for (auto it = timeline.begin(); it != timeline.end(); it++) {
        fprintf(stream, "%d ", it->first);
        for (auto lit = it->second.begin(); lit != it->second.end(); lit++) {
            fprintf(stream, "%d-%d ", lit->first, lit->second);
        }
        fprintf(stream, "\n");
    }
}

bool Schedule::eq(Schedule *s) {
    if (n != s->size()) return false;
    for (int i = 0; i < n; i++)
        if (ires[i] != s->ires[i])
            return false;
    return true;
}
