#include "../include/ProjectReader.h"

#include "../include/Project.h"

void ProjectReader::read(FILE *stream) {
  int n, res_count;
  fscanf(stream, "%d%d", &n, &res_count);
  Task **tasks = new Task *[n];
  int id, dur, ndep, nres;
  int *dep, *res;
  int *res_id = new int[res_count];
  double *res_sal = new double[res_count];
  for (int i = 0; i < res_count; i++) {
    fscanf(stream, "%d%lf", &res_id[i], &res_sal[i]);
  }
  for (int i = 0; i < n; i++) {
    fscanf(stream, "%d%d%d", &id, &dur, &ndep);
    dep = new int[ndep];
    for (int j = 0; j < ndep; j++)
      fscanf(stream, "%d", &dep[j]);
    fscanf(stream, "%d", &nres);
    res = new int[nres];
    for (int j = 0; j < nres; j++)
      fscanf(stream, "%d", &res[j]);
    // increment duration to match solutions
    tasks[i] = new Task(id, dur + 1, dep, res, ndep, nres);
  }
  Project::create(n, tasks, res_count, res_id, res_sal);
}
