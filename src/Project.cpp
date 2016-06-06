#include "../include/Project.h"

Project* Project::_project = 0;

void Project::create(int _n, Task** _tasks, int _res_count, int* _res_id, double* _res_sal) {
    _project = new Project(_n, _tasks, _res_count, _res_id, _res_sal);
}

Project::~Project() {
    for (int i = 0; i < n; i++)
        delete tasks[i];
    delete[] tasks;
    delete[] res_id;
    delete[] res_salary;
}

Project* Project::get() {
    return _project;
}

int Project::size() {
    return n;
}

int Project::get_res_count() {
    return res_count;
}

int Project::get_res_id(int res) {
    return res_id[res];
}

double Project::get_salary(int res) {
    return res_salary[res];
}

void Project::remove() {
    delete _project;
}