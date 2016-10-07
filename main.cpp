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
  if (argc != 2) {
    fprintf(stderr, "Invalid number of arguments.\n"
        "Usage: %s input_file [flags...]\n", argv[0]);
    return 1;
  }

  if (FLAGS_tournament_size == -1) {
    FLAGS_tournament_size = FLAGS_pop_size / 20;
  }

  printf("Tournament size: %d\n", FLAGS_tournament_size);

  std::string input_full_name = std::string(argv[1]);
  std::string input_base_name =
      input_full_name.substr(input_full_name.find_last_of("/\\") + 1);
  std::string folder_path =
      input_full_name.substr(0, input_full_name.find_last_of("/\\") + 1);
  std::string base_name = folder_path +
      input_base_name.substr(0, input_base_name.find_last_of('.'));
  printf("File base name: %s\n", input_base_name.c_str());
  printf("Folder path: %s\n", folder_path.c_str());
  printf("Base name: %s\n", base_name.c_str());

  FILE *input_file = fopen(input_full_name.c_str(), "r");
  ProjectReader::read(input_file);
  fclose(input_file);

  printf("Tasks: %d\n", Project::get()->size());

//    Schedule* s = new Schedule();
//    printf("FITNESS = %d\n", s->fitness());
//    s->show();

  Crossover<Schedule> *cross;
  if (FLAGS_lax) {
    cross = new LAXCrossover<Schedule>(FLAGS_crossover);
  } else {
    cross = new UniformCrossover<Schedule>(FLAGS_crossover);
  }
  Mutator<Schedule> *mut = new Mutator<Schedule>(FLAGS_mutation);
  Algorithm *algo = new Algorithm(FLAGS_pop_size, FLAGS_tournament_size,
                                  cross, mut, FLAGS_iters, false);

  std::string output_file_name = base_name;
  if (!FLAGS_suffix.empty()) {
    output_file_name += "." + FLAGS_suffix;
  }
  output_file_name += ".sol";
  FILE *output_file = fopen(output_file_name.c_str(), "w");

  Schedule *sch;
  if (FLAGS_output_stat) {
    std::string stat_file_name = base_name;
    if (!FLAGS_suffix.empty()) {
      stat_file_name += "." + FLAGS_suffix;
    }
    stat_file_name += ".stat";
    printf("Stat file name: %s\n", stat_file_name.c_str());
    FILE *stat_file = fopen(stat_file_name.c_str(), "w");

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
  FILE *best_file = fopen(best_file_name.c_str(), "w");
  fprintf(best_file, "%d", sch->fitness());

  sch->show(output_file);

  fclose(best_file);
  fclose(output_file);

  delete algo;
  Project::remove();

  return 0;
}
