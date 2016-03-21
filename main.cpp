#include <cstdio>
#include <cstring>
#include "include/ProjectReader.h"
#include "include/Project.h"
#include "include/Task.h"
#include "include/Schedule.h"
#include "include/Population.h"
#include "include/Selector.h"
#include "include/Mutator.h"
#include "include/Crossover.h"
#include "include/Algorithm.h"

const int POP_SIZE = 20;
const int N_STEPS = 20;
const double P_CROSS = 0.7;
const double P_MUT = 0.025;

int main() {
//    char file_name[] = "10_3_5_3";
    char file_name[] = "100_5_20_9_D3";
    printf("file name - %s\n", file_name);

    char input_file_name[50];
    strcat(strcpy(input_file_name, file_name), ".ndef");
    FILE* input_file = fopen(input_file_name, "r");

    ProjectReader::read(input_file);
    fclose(input_file);

//    int n = Project::get()->size();
//    printf("ntasks - %d\n", n);
//    for (int i = 0; i < n; i++) {
//        Task* task = Project::get()->tasks[i];
//        printf("> task id: %d, duration: %d, ndep: %d, nres: %d\n",
//            task->id, task->duration, task->dep.size(), task->res_size());
//    }
    printf("Tasks: %d\n", Project::get()->size());

    Schedule* s = new Schedule();
    printf("FITNESS = %d\n", s->fitness());

    Population *pop = new Population(POP_SIZE);
    Selector *sel = new Selector(5);
    Crossover *cross = new Crossover(P_CROSS);
    Mutator *mut = new Mutator(P_MUT);

    Algorithm *algo = new Algorithm(pop, sel, cross, mut, N_STEPS);

    char output_file_name[50];
    strcat(strcpy(output_file_name, file_name), ".sol");
    FILE* output_file = fopen(output_file_name, "w");

    Schedule *sch = algo->solve();

    printf("\nSOLUTION: ");
    sch->show();

    sch->show(output_file);

    fclose(output_file);

    return 0;
}
