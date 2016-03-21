#include "../include/Project.h"

Project* Project::_project = 0;

void Project::create(int _n, Task** _tasks) {
    _project = new Project(_n, _tasks);
}

Project::~Project() {
    for (int i = 0; i < n; i++)
        delete tasks[i];
    delete[] tasks;
}

Project* Project::get() {
    return _project;
}

int Project::size() {
    return n;
}
