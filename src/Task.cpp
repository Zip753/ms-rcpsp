#include "../include/Task.h"

Task::Task(int _id, int _dur, int _ndep, int *_dep, int _nres, int *_res)
    : id(_id), duration(_dur), res(_res), nres(_nres)  {
    if (_ndep > 0)
        dep = std::list<int>(_dep, _dep + _ndep);
    else
        dep = std::list<int>();
}

Task::Task(Task* t) : id(t->id), duration(t->duration), dep(t->dep), next(t->next), nres(t->nres) {
    res = new int[nres];
    for (int i = 0; i < nres; i++)
        res[i] = t->res[i];
}

Task::~Task() {
    delete[] res;
}

int Task::res_size() {
    return nres;
}

bool Task::collides_with(Task* t) {
    return start + duration > t->start
        && t->start + t->duration > start;
}
