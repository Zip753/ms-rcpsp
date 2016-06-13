#ifndef PROJECT_H
#define PROJECT_H

#include "Task.h"

/**
 * Singleton class that represents the project in the scheduling problem.
 */
class Project {
public:
    /**
     * Create singleton instance.
     */
    static void create(int _n, Task** _tasks, int _res_count, int* _res_id, double* _res_sal);

    /**
     * Delete singleton instance.
     */
    static void remove();

    /**
     * Get singleton instance.
     */
    static Project* get();

    ~Project();

    /**
     * Number of tasks in the project.
     */
    int size();

    /**
     * Number of resources in the project.
     */
    int get_res_count();

    /**
     * Returns resource ID of the resource at the given index.
     * @param res index of the resource
     */
    int get_res_id(int res);

    /**
     * Returns the hourly salary of the resource at the given index.
     * @param res index of the resource
     */
    double get_salary(int res);

    /**
     * List of the tasks in the project.
     */
    Task** tasks;
private:
    /**
     * List of IDs of resources.
     */
    int *res_id;

    /**
     * List of salaries of resources.
     */
    double *res_salary;

    /**
     * Number of tasks.
     */
    int n;

    /**
     * Number of resources.
     */
    int res_count;

    /**
     * Variable that holds the instance of Project class.
     */
    static Project* _project;

    /**
     * @see ProjectReader::read()
     */
    Project(int _n, Task** _tasks, int _res_count, int* _res_id, double* _res_sal)
            : n(_n), tasks(_tasks), res_count(_res_count), res_id(_res_id), res_salary(_res_sal) {};
};

#endif // PROJECT_H
