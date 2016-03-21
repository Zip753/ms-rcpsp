#include "../include/ProjectReader.h"
#include "../include/Project.h"
#include "../include/Task.h"

void ProjectReader::read(FILE* stream) {
    int n;
    fscanf(stream, "%d", &n);
    Task** tasks = new Task*[n];
    int id, dur, ndep, nres;
    int *dep, *res;
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
        tasks[i] = new Task(id, dur + 1, ndep, dep, nres, res);
    }
    Project::create(n, tasks);
}
