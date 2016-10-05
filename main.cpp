#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

#include <gflags/gflags.h>

#include "include/ProjectReader.h"
#include "include/Project.h"
#include "include/Schedule.h"
#include "include/Population.h"
#include "include/Selector.h"
#include "include/Mutator.h"
#include "include/LAXCrossover.h"
#include "include/Algorithm.h"
#include "include/UniformCrossover.h"

DEFINE_string(filename, "", "Input project file.");
DEFINE_int32(pop_size, 100, "Population size.");
DEFINE_int32(iters, 200, "Number of generations.");
DEFINE_double(crossover, 0.3, "Probability of crossover.");
DEFINE_double(mutation, 0.01, "Probability of single gene mutation.");
DEFINE_int32(tournament_size, -1, "Size of tournament for selection.");
DEFINE_string(suffix, "", "Suffix for output file names.");
DEFINE_bool(lax, false, "Use LAX crossover operator.");
DEFINE_bool(output_stat, false, "Output population statistics to .stat file.");

int main(int argc, char *argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_filename.empty()) {
        fprintf(stderr, "No input file provided.");
        return 1;
    }

    if (FLAGS_tournament_size == -1) {
        FLAGS_tournament_size = FLAGS_pop_size / 20;
    }

    printf("Tournament size: %d\n", FLAGS_tournament_size);

    std::string base_name = "data/" + FLAGS_filename + "/" + FLAGS_filename;
    printf("File name: %s\n", base_name.c_str());

    std::string input_file_name = base_name + ".ndef";
    FILE* input_file = fopen(input_file_name.c_str(), "r");
    ProjectReader::read(input_file);
    fclose(input_file);

    printf("Tasks: %d\n", Project::get()->size());

//    Schedule* s = new Schedule();
//    printf("FITNESS = %d\n", s->fitness());
//    s->show();

    Population *pop = new Population(FLAGS_pop_size);
    Selector *sel = new Selector(FLAGS_tournament_size);
    Crossover *cross;
    if (FLAGS_lax) {
        cross = new LAXCrossover(FLAGS_crossover);
    } else {
        cross = new UniformCrossover(FLAGS_crossover);
    }
    Mutator *mut = new Mutator(FLAGS_mutation);
    Algorithm *algo = new Algorithm(pop, sel, cross, mut, FLAGS_iters, false);

    std::string output_file_name = base_name;
    if (!FLAGS_suffix.empty()) {
        output_file_name += "." + FLAGS_suffix;
    }
    output_file_name += ".sol";
    FILE* output_file = fopen(output_file_name.c_str(), "w");

    Schedule *sch;
    if (FLAGS_output_stat) {
        std::string stat_file_name = base_name;
        if (!FLAGS_suffix.empty()) {
            stat_file_name += "." + FLAGS_suffix;
        }
        stat_file_name += ".stat";
        printf("Stat file name: %s\n", stat_file_name.c_str());
        FILE* stat_file = fopen(stat_file_name.c_str(), "w");

        sch = algo->solve(stat_file);
        fclose(stat_file);
    } else {
        sch = algo->solve(nullptr);
    }

    printf("SOLUTION: ");
    sch->show(true);

    std::string best_file_name = base_name;
    if (!FLAGS_suffix.empty()) {
        best_file_name += "." + FLAGS_suffix;
    }
    best_file_name += ".best";
    FILE* best_file = fopen(best_file_name.c_str(), "w");
    fprintf(best_file, "%d", sch->fitness());

    sch->show(output_file);

    fclose(best_file);
    fclose(output_file);

    delete algo;
    Project::remove();

    return 0;
}
