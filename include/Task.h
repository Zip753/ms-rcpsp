#ifndef TASK_H
#define TASK_H

#include <list>

class Task {
public:
    Task(int _id, int _dur, int _ndep, int *_dep, int _nres, int *_res)
            : id(_id), duration(_dur), ndep(_ndep), dep(_dep), res(_res), nres(_nres)  {};
    ~Task();
    int id, duration;
    int *res, *dep;
    int res_size();
    int dep_size();
private:
    int nres, ndep;
};

#endif // TASK_H
