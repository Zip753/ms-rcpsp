/**
 * Example of library usage. Reads project from file and finds a suboptimal
 * feasible schedule.
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>

#include <gflags/gflags.h>

#include "include/ProjectReader.h"
#include "include/Project.h"
#include "include/Schedule.h"
#include "include/Mutator.h"
#include "include/LAXCrossover.h"
#include "include/GeneticAlgorithm.h"
#include "include/UniformCrossover.h"
#include "include/PrioSchedule.h"
#include "include/SimpleSchedule.h"
#include "include/TournamentSelector.h"
#include "include/SimpleMutator.h"

DEFINE_int32(pop_size, 100, "Population size.");
DEFINE_int32(iters, 200, "Number of generations.");
DEFINE_double(crossover, 0.3, "Probability of crossover.");
DEFINE_double(mutation, 0.01, "Probability of single gene mutation.");
DEFINE_int32(tournament_size, -1, "Size of tournament for selection.");
DEFINE_string(suffix, "", "Suffix for output file names.");
DEFINE_bool(lax, false, "Use LAX crossover operator.");
DEFINE_bool(output_stat, false, "Output population statistics to .stat file.");
DEFINE_bool(simple, false, "Use simple schedule representation.");

template <class T>
std::shared_ptr<T> InitAndSolve(const std::string& stat_file_name) {
  std::shared_ptr<Selector<T>> sel =
      std::make_shared<TournamentSelector<T>>(FLAGS_tournament_size);
  std::shared_ptr<Crossover<T>> cross;
  if (FLAGS_lax) {
    cross = std::make_shared<LAXCrossover<T>>(FLAGS_crossover);
  } else {
    cross = std::make_shared<UniformCrossover<T>>(FLAGS_crossover);
  }
  std::shared_ptr<Mutator<T>> mut =
      std::make_shared<SimpleMutator<T>>(FLAGS_mutation);
  GeneticAlgorithm<T> algo(FLAGS_pop_size, sel, cross, mut, FLAGS_iters, false);
  std::shared_ptr<T> sch;
  if (FLAGS_output_stat) {
    FILE* stat_file = fopen(stat_file_name.c_str(), "w");
    sch = std::move(algo.solve(stat_file));
    fclose(stat_file);
  } else {
    sch = std::move(algo.solve(nullptr));
  }
  return sch;
}

template <class T>
void SolveAndOutput(const std::string& stat_file_name,
                    FILE* output_file,
                    FILE* best_file) {
  std::shared_ptr<Schedule> sch = std::move(InitAndSolve<T>(stat_file_name));

  /* Output solution to stdout. */
  printf("SOLUTION: ");
  sch->printState(true);

  /* Output solution to file. */
  sch->writeToFile(output_file);

  /* Output best fitness value to file. */
  fprintf(best_file, "%d", sch->fitness());
}

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (argc != 2) {
    fprintf(stderr, "Invalid number of arguments.\n"
        "Usage: %s input_file [flags...]\n", argv[0]);
    return 1;
  }

  /* Set tournament size dynamically, if none provided. */
  if (FLAGS_tournament_size == -1) {
    FLAGS_tournament_size = FLAGS_pop_size / 20;
  }
  printf("Tournament size: %d\n", FLAGS_tournament_size);

  /* Parse filename. */
  std::string input_full_name = std::string(argv[1]);
  std::string input_base_name =
      input_full_name.substr(input_full_name.find_last_of("/\\") + 1);
  std::string folder_path =
      input_full_name.substr(0, input_full_name.find_last_of("/\\") + 1);
  std::string base_name = folder_path +
      input_base_name.substr(0, input_base_name.find_last_of('.'));

  /* Read project data from file. */
  if (!ProjectReader::read(input_full_name)) {
    fprintf(stderr, "Invalid input file format.\n");
    return 1;
  }
  printf("Tasks: %d\n", Project::get()->size());

  /* Project solution output: */
  std::string output_file_name = base_name;
  if (!FLAGS_suffix.empty()) {
    output_file_name += "." + FLAGS_suffix;
  }
  output_file_name += ".sol";
  FILE* output_file = fopen(output_file_name.c_str(), "w");

  /* Population statistics output: */
  std::string stat_file_name = base_name;
  if (!FLAGS_suffix.empty()) {
    stat_file_name += "." + FLAGS_suffix;
  }
  stat_file_name += ".stat";

  /* Minimum fitness output: */
  std::string best_file_name = base_name;
  if (!FLAGS_suffix.empty()) {
    best_file_name += "." + FLAGS_suffix;
  }
  best_file_name += ".best";
  FILE* best_file = fopen(best_file_name.c_str(), "w");

  /* Run the algorithm. */
  if (FLAGS_simple) {
    SolveAndOutput<SimpleSchedule>(stat_file_name, output_file, best_file);
  } else {
    SolveAndOutput<PrioSchedule>(stat_file_name, output_file, best_file);
  }

  fclose(output_file);
  fclose(best_file);

  return 0;
}
