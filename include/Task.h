#ifndef TASK_H
#define TASK_H

#include <list>

class Task {
public:
    /**
     * Create task using given ID, dependencies and capable resources.
     * @param _id ID of the task.
     * @param _dur duration of the task.
     * @param _ndep number of dependencies.
     * @param _dep list of dependencies.
     * @param _nres number of capable resources.
     * @param _res list of capable resources.
     */
    Task(int _id, int _dur, int _ndep, int *_dep, int _nres, int *_res)
            : id(_id), duration(_dur), ndep(_ndep), dep(_dep), res(_res), nres(_nres)  {};
    ~Task();

    /**
     * Task ID.
     */
    int id;

    /**
     * Task duration.
     */
    int duration;

    /**
     * List of resources capable of completing the task.
     */
    int *res;

    /**
     * List of dependencies.
     */
    int *dep;

    /**
     * Number of resources capable of completing the task.
     */
    int res_size();

    /**
     * Number of dependencies.
     */
    int dep_size();
private:
    int nres, ndep;
};

#endif // TASK_H
