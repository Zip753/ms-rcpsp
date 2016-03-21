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

    tasks = new Task*[n + 2];
    for (int i = 0; i < n; i++)
        tasks[i] = new Task(proj->tasks[i]);

    st = tasks[n] = new Task(-1, 0, 0, 0, 0, 0);
    fin = tasks[n + 1] = new Task(-1, 0, 0, 0, 0, 0);

    // connect everything to first task
    for (int i = 0; i < n; i++) {
        if (tasks[i]->dep.empty())
            tasks[i]->dep.push_back(n);
    }

    // add reverse connections
    for (int i = 0; i < n + 1; i++) {
        for (auto it = tasks[i]->dep.begin(); it != tasks[i]->dep.end(); it++) {
            int to = *it;
            tasks[to]->next.push_back(i);
//            printf(">> %d -> %d\n", to + 1, i + 1);
        }
    }

    // connect everything to last task
    for (int i = 0; i < n; i++)
        if (tasks[i]->next.empty()) {
            tasks[i]->next.push_back(n + 1);
            fin->dep.push_back(i);
//            printf(">> %d -> %d\n", i + 1, n + 2);
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
    if (tasks[i]->dep.empty())
        tasks[i]->start = 0;
    else {
        int start = -1;
        for (auto it = tasks[i]->dep.begin(); it != tasks[i]->dep.end(); it++) {
            int prev = *it;
            int finish = tasks[prev]->start + tasks[prev]->duration;
            if (finish > start)
                start = finish;
        }
        tasks[i]->start = start;
    }
}

void Schedule::update_finish(int i) {
    for (auto it = tasks[i]->next.begin(); it != tasks[i]->next.end(); it++) {
        int next = *it;
        update_finish(next);
    }
    if (tasks[i]->next.empty())
        tasks[i]->finish = tasks[i]->start + tasks[i]->duration;
    else {
        int finish = -1;
        for (auto it = tasks[i]->next.begin(); it != tasks[i]->next.end(); it++) {
            int next = *it;
            int start = tasks[next]->start;
            if (start < finish)
                finish = start;
        }
        tasks[i]->finish = finish;
    }
}

void Schedule::reschedule() {
    // first, set earliest start (from fin to st)
    update_start(n + 1);
    // second, set latest finish (from st to fin)
    update_finish(n);
}

std::pair<int, int> Schedule::check_conflict() {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (tasks[i]->res[ires[i]] == tasks[j]->res[ires[j]]
            && tasks[i]->collides_with(tasks[j]))
                return std::make_pair(i, j);
    return std::make_pair(-1, -1);
//    for (int i = 0; i < n; i++) {
//        int res = tasks[i]->res[ires[i]];
//        if (checked_res.find(res) == checked_res.end()) {
//            // lista indeksow taskow przypisanych dla zasobu res
//            std::vector<int> lst;
//            for (int j = 0; j < n; j++)
//                if (tasks[j]->res[ires[j]] == res)
//                    lst.push_back(j);
//
//            std::sort(lst.begin(), lst.end(), Comparator(tasks));
////            printf("res: %d, checked: %d, lst[0]: %d\n", res, checked_res.size(), lst[0]);
//
//            for (size_t j = 1; j < lst.size(); j++) {
//                int ii = lst[j - 1],
//                    jj = lst[j];
//                if (tasks[ii]->start + tasks[ii]->duration > tasks[jj]->start)
//                    return std::make_pair(ii, jj);
////                if (tasks[jj]->start + tasks[jj]->duration > tasks[ii]->start)
////                    return std::make_pair(jj, ii);
//            }
//            checked_res.insert(res);
//        }
//    }
//    return std::make_pair(-1, -1);
}

int Schedule::fitness() {
    if (_fitness == -1) {
        reschedule();
        std::pair<int, int> conf = check_conflict();
        int cnt = 0;
        while (conf.first != -1) {
            int i = conf.first,
                j = conf.second;
            tasks[i]->next.push_back(j);
            tasks[j]->dep.push_back(i);
            reschedule();
            conf = check_conflict();
//            printf("conflict: %d -> %d\n", conf.first, conf.second);
            cnt++;
            if (cnt % 50 == 0)
                printf("> cnt = %d\n", cnt);
        }
        _fitness = fin->finish;
    }
    return _fitness;
}

int Schedule::size() {
    return n;
}

int Schedule::max_res_count(int i) {
    return tasks[i]->res_size();
}

void Schedule::show() {
    for (int i = 0; i < n; i++)
        printf("%d: %d, ", tasks[i]->id, tasks[i]->res[ires[i]]);
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
