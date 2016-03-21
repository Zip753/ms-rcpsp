#ifndef TASK_H
#define TASK_H

#include <list>

class Task {
public:
    Task(int _id, int _dur, int _ndep, int *_dep, int _nres, int *_res);
    Task(Task* t);
    ~Task();
    int id, duration;
    std::list<int> dep, next;
    int *res;
    int res_size();
    int start, finish; // earliest start and latest finish
    bool collides_with(Task* t);
private:
    int nres;
};

#endif // TASK_H
