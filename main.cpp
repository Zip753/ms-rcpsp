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

#include "include/GeneticAlgorithm.h"
#include "include/LAXCrossover.h"
#include "include/Mutator.h"
#include "include/PrioSchedule.h"
#include "include/Project.h"
#include "include/ProjectReader.h"
#include "include/Schedule.h"
#include "include/SimpleMutator.h"
#include "include/SimpleSchedule.h"
#include "include/TabuSearchAlgorithm.h"
#include "include/TournamentSelector.h"
#include "include/UniformCrossover.h"
#include "include/Validator.h"

const int FLAGS_pop_size = 100;
const int FLAGS_iters = 200;
const double FLAGS_crossover = 0.3;
const double FLAGS_mutation = 0.01;
int FLAGS_tournament_size = -1;
const std::string FLAGS_suffix = "";
const bool FLAGS_lax = false;
const bool FLAGS_output_stat = true;
bool FLAGS_simple = false;

using namespace EvolutionaryAlgorithm;
using namespace SchedulingProblem;

template <class T>
std::unique_ptr<T> InitAndSolve(const std::string& stat_file_name) {
  std::unique_ptr<Selector<T>> sel =
      std::make_unique<TournamentSelector<T>>(FLAGS_tournament_size);
  std::unique_ptr<Crossover<T>> cross;
  if (FLAGS_lax) {
    cross = std::make_unique<LAXCrossover<T>>(FLAGS_crossover);
  } else {
    cross = std::make_unique<UniformCrossover<T>>(FLAGS_crossover);
  }
  std::unique_ptr<Mutator<T>> mut =
      std::make_unique<SimpleMutator<T>>(FLAGS_mutation);
  std::unique_ptr<Algorithm<T>> algo =
//      std::make_unique<GeneticAlgorithm<T>>(FLAGS_pop_size,
//                                            std::move(sel),
//                                            std::move(cross),
//                                            std::move(mut),
//                                            FLAGS_iters,
//                                            false);
      std::make_unique<TabuSearchAlgorithm<T>>(500, 100, 100, 0.01);
  std::unique_ptr<T> sch = nullptr;
  if (FLAGS_output_stat) {
    FILE* stat_file = fopen(stat_file_name.c_str(), "w");
    sch = std::move(algo->optimize(stat_file));
    fclose(stat_file);
  } else {
    sch = std::move(algo->optimize());
  }
  // Force fitness computation to set start dates properly.
  sch->fitness();
  auto valid = Validator::validate(*sch);
  if (!valid.first) {
    printf("The solution is invalid!\n%s\n", valid.second.c_str());
  } else {
    printf("The solution is valid.\n");
  }
  return sch;
}

template <class T>
void SolveAndOutput(const std::string& stat_file_name,
                    FILE* output_file,
                    FILE* best_file) {
  std::unique_ptr<Schedule> sch(InitAndSolve<T>(stat_file_name));

  /* Output solution to stdout. */
  printf("SOLUTION: ");
  sch->printState(true);

  /* Output solution to file. */
  sch->writeToFile(output_file);

  /* Output best fitness value to file. */
  fprintf(best_file, "%d", sch->fitness());
}

int main(int argc, char* argv[]) {
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Invalid number of arguments.\n"
        "Usage: %s input_file [flags...]\n", argv[0]);
    return 1;
  }

  std::string input_full_name;
  if (argc == 3) {
    if (strcmp(argv[1], "--simple") == 0) {
      input_full_name = std::string(argv[2]);
      FLAGS_simple = true;
    } else if (strcmp(argv[2], "--simple") == 0) {
      input_full_name = std::string(argv[1]);
      FLAGS_simple = true;
    } else {
      fprintf(stderr, "Invalid flags.\n"
          "Usage: %s input_file [flags...]\n", argv[0]);
      return 1;
    }
  } else {
    input_full_name = std::string(argv[1]);
  }

  /* Set tournament size dynamically, if none provided. */
  if (FLAGS_tournament_size == -1) {
    FLAGS_tournament_size = FLAGS_pop_size / 20;
  }
  printf("Tournament size: %d\n", FLAGS_tournament_size);

  /* Parse filename. */
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
  printf("Tasks: %d\n", Project::size());

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
