#ifndef PROJECT_H
#define PROJECT_H

#include "Task.h"

class Project {
public:
    static void create(int _n, Task** _tasks);
    static Project* get();
    ~Project();

    int size();
    Task** tasks;
private:
    int n;
    static Project* _project;
    Project(int _n, Task** _tasks) : tasks(_tasks), n(_n) {}
};

#endif // PROJECT_H
