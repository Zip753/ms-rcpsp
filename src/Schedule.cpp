#include "../include/Schedule.h"
#include "../include/Project.h"
#include "../include/Random.h"
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

void Schedule::init(bool initialize) {
    Project* proj = Project::get();
    n = proj->size();
    this->tasks = proj->tasks;

    if (initialize) {
        ires = new int[n];
        prio = new int[n];
        for (int i = 0; i < n; i++) {
            ires[i] = Random::randint() % proj->tasks[i]->res_size();
            prio[i] = i;
        }
        std::random_shuffle(prio, prio + n);
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
    prio = new int[n];
    for (int i = 0; i < n; i++) {
        ires[i] = s->ires[i];
        prio[i] = s->prio[i];
    }
}

Schedule::Schedule(int *_ires, int *_prio) : ires(_ires), prio(_prio) {
    init(false);
}

Schedule::~Schedule() {
    delete[] ires;
    delete[] prio;
    delete[] start;
    delete[] visited;
}

void Schedule::fix_all(std::list<std::pair<int, int> > *assigned) {
    struct PriorityComp {
        bool operator()(const std::pair<int, int> a, const std::pair<int, int> b) const {
            return a.second < b.second;
        }
    };

    // heap of pairs (task_id, priority)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, PriorityComp> queue;
    for (int i = 0; i < n; ++i) {
        if (tasks[i]->dep_size() == 0) {
            queue.push(std::make_pair(i, prio[i]));
        }
    }
    int res_count = Project::get()->get_res_count();

    // availability time for resources
    int* time = new int[res_count];
    std::fill_n(time, res_count, 0);

    // number of complete dependencies for tasks
    int* dep_count = new int[n];
    std::fill_n(dep_count, n, 0);

    while (!queue.empty()) {
        // take next task
        int itask = queue.top().first;
        queue.pop();

        // find max finish time of all dependencies
        int res_idx = resource(itask);
        int min_start = 0;
        for (int i = 0; i < tasks[itask]->dep_size(); ++i) {
            int idep = tasks[itask]->dep[i];
            int fin = finish_time(idep);
            if (min_start < fin)
                min_start = fin;
        }

        // update start time for the task
        start[itask] = std::max(min_start, time[res_idx]);
        // update availability time for resource
        time[res_idx] = finish_time(itask);
        // add task to assigned
        assigned[res_idx].push_back(std::make_pair(finish_time(itask), itask));

        // add all unblocked dependent tasks to the queue
        for (int i = 0; i < tasks[itask]->next_size; ++i) {
            int inext = tasks[itask]->next[i];
            dep_count[inext]++;
            if (dep_count[inext] == tasks[inext]->dep_size()) {
                queue.push(std::make_pair(inext, prio[inext]));
            }
        }
    }

    delete[] time;
    delete[] dep_count;
}

int Schedule::resource(int i) {
    return tasks[i]->res[ires[i]];
}

int Schedule::finish_time(int i) {
    return start[i] + tasks[i]->duration;
}

int Schedule::fitness() {
    if (_fitness == -1) {
        std::list<std::pair<int, int> > *assigned = new std::list<std::pair<int, int> >[n];

        fix_all(assigned);

//        // execute heuristics several times
//        for (int k = 0; k < 5; ++k) {

            bool not_found = true;
            for (int i = 0; not_found && i < n; ++i) {
                // start of current task
                int st = start[i];
                for (int j = 0; not_found && j < tasks[i]->res_size(); ++j) {
                    // for any other resource
                    if (ires[i] != j) {
                        // find first task that starts not earlier than current
                        auto it = std::lower_bound(assigned[i].begin(), assigned[i].end(), std::make_pair(st, -1));
                        // if no such task is found or our task fits before the found one
                        if (it == assigned[i].end() || finish_time(i) <= it->first) {
                            // if there are no earlier tasks, swap resource and terminate
                            if (it == assigned[i].begin()) {
                                ires[i] = j;
                                not_found = false;
                            } else {
                                // otherwise check previous task
                                it--;
                                // if there is no conflict, then swap resources and terminate
                                if (finish_time(it->second) <= st) {
                                    ires[i] = j;
                                    not_found = false;
                                }
                            }
                        }
                    }
                }
            }

            fix_all(assigned);

//        }

        delete[] assigned;

        for (int i = 0; i < n; i++)
            if (_fitness < finish_time(i))
                _fitness = finish_time(i);

        std::fill_n(business, Project::get()->get_res_count(), 0);
        for (int i = 0; i < n; i++) {
            int res = resource(i);
            business[res] += tasks[i]->duration;
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
