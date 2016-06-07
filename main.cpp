#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "include/ProjectReader.h"
#include "include/Project.h"
#include "include/Schedule.h"
#include "include/Population.h"
#include "include/Selector.h"
#include "include/Mutator.h"
#include "include/LAXCrossover.h"
#include "include/Algorithm.h"
#include "include/UniformCrossover.h"

char *fname;
char file_name[123];
int POP_SIZE = 100;
int N_STEPS = 200;
double P_CROSS = 0.3;
double P_MUT = 0.01;
int TOURN_SIZE;
char *suffix = nullptr;

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        fname = argv[1];
    } else {
        fname = new char[123];
        strcpy(fname, "100_5_20_9_D3");
    }
    if (argc >= 3) { POP_SIZE = atoi(argv[2]); }
    if (argc >= 4) { N_STEPS = atoi(argv[3]); }
    if (argc >= 5) { P_CROSS = atof(argv[4]); }
    if (argc >= 6) { P_MUT = atof(argv[5]); }
    if (argc >= 7 && strlen(argv[6]) > 0) { TOURN_SIZE = atoi(argv[6]); }
    else TOURN_SIZE = POP_SIZE / 20;
    if (argc >= 8 && strlen(argv[7]) > 0) { suffix = argv[7]; }

    printf("TOURN_SIZE - %d\n", TOURN_SIZE);

    strcpy(file_name, "data/");
    strcat(file_name, fname);
    strcat(file_name, "/");
    strcat(file_name, fname);
    printf("file name - %s\n", file_name);

    char input_file_name[123];
    strcat(strcpy(input_file_name, file_name), ".ndef");
    FILE* input_file = fopen(input_file_name, "r");

    ProjectReader::read(input_file);
    fclose(input_file);

    printf("Tasks: %d\n", Project::get()->size());

//    Schedule* s = new Schedule();
//    printf("FITNESS = %d\n", s->fitness());
//    s->show();

    Population *pop = new Population(POP_SIZE);
    Selector *sel = new Selector(TOURN_SIZE);
//    Crossover *cross = new LAXCrossover(P_CROSS);
    Crossover *cross = new UniformCrossover(P_CROSS);
    Mutator *mut = new Mutator(P_MUT);

    Algorithm *algo = new Algorithm(pop, sel, cross, mut, N_STEPS, false);

    char output_file_name[123];
    strcpy(output_file_name, file_name);
    if (suffix != nullptr) {
        strcat(output_file_name, ".");
        strcat(output_file_name, suffix);
    }
    strcat(output_file_name, ".sol");
    FILE* output_file = fopen(output_file_name, "w");

    Schedule *sch;

    bool SHOW_STAT = true;
    if (SHOW_STAT) {
        char stat_file_name[123];
        strcpy(stat_file_name, file_name);
        if (suffix != nullptr) {
            strcat(stat_file_name, ".");
            strcat(stat_file_name, suffix);
        }
        strcat(stat_file_name, ".stat");
        FILE* stat_file = fopen(stat_file_name, "w");

        sch = algo->solve(stat_file);;
        fclose(stat_file);
    } else {
        sch = algo->solve(nullptr);
    }

    printf("SOLUTION: ");
    sch->show(true);

    char best_file_name[123];
    strcpy(best_file_name, file_name);
    if (suffix != nullptr) {
        strcat(best_file_name, ".");
        strcat(best_file_name, suffix);
    }
    strcat(best_file_name, ".best");
    FILE* best_file = fopen(best_file_name, "w");
    fprintf(best_file, "%d", sch->fitness());

    sch->show(output_file);

    fclose(best_file);
    fclose(output_file);

    delete algo;
    Project::remove();

    return 0;
}
