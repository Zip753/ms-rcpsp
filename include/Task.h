#ifndef MS_RCPSP_TASK_H
#define MS_RCPSP_TASK_H

class Task {
 public:
  Task(int _id, int _dur, int *_dep, int *_res, int _ndep, int _nres)
      : id(_id), duration(_dur), dep(_dep), res(_res), ndep(_ndep),
        nres(_nres) {};
  ~Task();
  int id, duration;
  int *dep, *res, *next;
  int res_size();
  int dep_size();
  int next_size;

 private:
  int ndep, nres;
};

#endif // MS_RCPSP_TASK_H
