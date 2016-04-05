#ifndef PROJECT_H
#define PROJECT_H

#include "Task.h"

class Project {
public:
    static void create(int _n, Task** _tasks, int _res_count, int* _res_id, double* _res_sal);
    static Project* get();
    ~Project();

    int size();
    int get_res_count();
    int get_res_id(int res);
    double get_salary(int res);
    Task** tasks;
private:
    int *res_id;
    double *res_salary;
    int n;
    int res_count;
    static Project* _project;
    Project(int _n, Task** _tasks, int _res_count, int* _res_id, double* _res_sal)
            : n(_n), tasks(_tasks), res_count(_res_count), res_id(_res_id), res_salary(_res_sal) {};
};

#endif // PROJECT_H
