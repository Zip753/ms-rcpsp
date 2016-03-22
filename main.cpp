#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "include/ProjectReader.h"
#include "include/Project.h"
#include "include/Task.h"
#include "include/Schedule.h"
#include "include/Population.h"
#include "include/Selector.h"
#include "include/Mutator.h"
#include "include/Crossover.h"
#include "include/Algorithm.h"

char *file_name;
int POP_SIZE = 100;
int N_STEPS = 100;
double P_CROSS = 0.7;
double P_MUT = 0.03;

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        file_name = argv[1];
    } else {
        file_name = new char[20];
        strcpy(file_name, "10_3_5_3");
    }
    if (argc >= 3) { POP_SIZE = atoi(argv[2]); }
    if (argc >= 4) { N_STEPS = atoi(argv[3]); }
    if (argc >= 5) { P_CROSS = atoi(argv[4]); }
    if (argc >= 6) { P_MUT = atoi(argv[5]); }
//    char file_name[] = "15_6_10_6";
//    char file_name[] = "100_5_20_9_D3";
//    char file_name[] = "100_20_65_9";
//    char file_name[] = "200_40_130_9_D4";
    printf("file name - %s\n", file_name);

    char input_file_name[50];
    strcat(strcpy(input_file_name, file_name), ".ndef");
    FILE* input_file = fopen(input_file_name, "r");

    ProjectReader::read(input_file);
    fclose(input_file);

    printf("Tasks: %d\n", Project::get()->size());

//    Schedule* s = new Schedule();
//    printf("FITNESS = %d\n", s->fitness());
//    s->show();

    Population *pop = new Population(POP_SIZE);
    Selector *sel = new Selector(5);
    Crossover *cross = new Crossover(P_CROSS);
    Mutator *mut = new Mutator(P_MUT);

    Algorithm *algo = new Algorithm(pop, sel, cross, mut, N_STEPS);

    char output_file_name[50];
    strcat(strcpy(output_file_name, file_name), ".sol");
    FILE* output_file = fopen(output_file_name, "w");

    char stat_file_name[50];
    strcat(strcpy(stat_file_name, file_name), ".stat");
    FILE* stat_file = fopen(stat_file_name, "w");

    Schedule *sch = algo->solve(stat_file);

    printf("\nSOLUTION: ");
    sch->show(true);

    sch->show(output_file);

    fclose(output_file);


    printf("ARGC: %d\n", argc);

    return 0;
}
