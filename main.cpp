/**
 * Example of library usage. Reads project from file and finds a suboptimal
 * feasible schedule.
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "include/GeneticAlgorithm.h"
#include "include/LAXCrossover.h"
#include "include/Mutator.h"
#include "include/PrioSchedule.h"
#include "include/Project.h"
#include "include/ProjectReader.h"
#include "include/Schedule.h"
#include "include/ScheduleWriter.h"
#include "include/SimpleSchedule.h"
#include "include/SimulatedAnnealing.h"
#include "include/TabuSearch.h"
#include "include/TournamentSelector.h"
#include "include/UniformCrossover.h"
#include "include/UniformMutator.h"
#include "include/Validator.h"

const int FLAGS_pop_size = 100;
const int FLAGS_iters = 50000;
const double FLAGS_temp = 1000;
const double FLAGS_eps = 1e-3;
const int FLAGS_list_size = 100;
const double FLAGS_crossover = 0.3;
const double FLAGS_mutation = 0.01;
int FLAGS_tournament_size = -1;
std::string FLAGS_suffix = "";
const bool FLAGS_lax = false;
const bool FLAGS_output_stat = true;
bool FLAGS_simple = false;

using namespace SchedulingProblem;
using namespace Solutions;
using namespace Solutions::EvolutionaryAlgorithm;

template <class T>
std::unique_ptr<Population<T>> BuildPopulation(size_t pop_size,
                                               Project* project) {
  std::vector<std::unique_ptr<T>> specimen;
  specimen.reserve(pop_size);
  for (size_t i = 0; i < pop_size; ++i) {
    specimen.push_back(std::move(std::make_unique<T>(project)));
  }
  return std::move(std::make_unique<Population<T>>(&specimen));
}

template <class T>
std::unique_ptr<T> InitAndSolve(const std::string& stat_file_name,
                                Project* project) {
  std::unique_ptr<Selector<T>> sel =
      std::make_unique<TournamentSelector<T>>(FLAGS_tournament_size);
  std::unique_ptr<Crossover<T>> cross;
  if (FLAGS_lax) {
    cross = std::make_unique<LAXCrossover<T>>(FLAGS_crossover);
  } else {
    cross = std::make_unique<UniformCrossover<T>>(FLAGS_crossover);
  }
  std::unique_ptr<Mutator<T>> mut =
      std::make_unique<UniformMutator<T>>(FLAGS_mutation);
  std::unique_ptr<Population<T>> pop =
      std::move(BuildPopulation<T>(FLAGS_pop_size, project));
  std::unique_ptr<Algorithm<T>> algo =
      std::make_unique<GeneticAlgorithm<T>>(std::move(pop),
                                            std::move(sel),
                                            std::move(cross),
                                            std::move(mut),
                                            FLAGS_iters,
                                            false);
//      std::make_unique<SimulatedAnnealing<T>>(T(project),
//                                                       FLAGS_iters,
//                                                       FLAGS_temp,
//                                                       FLAGS_mutation,
//                                                       FLAGS_eps);
//      std::make_unique<TabuSearch<T>>(T(project),
//                                               FLAGS_iters,
//                                               FLAGS_pop_size,
//                                               FLAGS_list_size,
//                                               FLAGS_mutation);
  std::unique_ptr<T> sch = nullptr;
  if (FLAGS_output_stat) {
    std::ofstream stat_file(stat_file_name);
    sch = std::move(algo->optimize(stat_file));
  } else {
    sch = std::move(algo->optimize());
  }
  // Force fitness computation to set start dates properly.
  sch->fitness();
  auto valid = Validator::Validate(*sch);
  if (!valid.first) {
    std::cout << "The solution is invalid!\n" << valid.second.c_str() << "\n";
  } else {
    std::cout << "The solution is valid.\n";
  }
  return sch;
}

template <class T>
void SolveAndOutput(const std::string& stat_file_name,
                    std::ofstream& output_file,
                    std::ofstream& best_file,
                    Project* project) {

  std::unique_ptr<Schedule> sch(InitAndSolve<T>(stat_file_name, project));

  /* Output solution to stdout. */
  std::cout << "SOLUTION: ";
  sch->PrintState(true);

  /* Output solution to file. */
  ScheduleWriter::Write(output_file, *sch);

  /* Output best fitness value to file. */
  best_file << sch->fitness();
}

int main(int argc, char* argv[]) {
  if (argc < 4 || argc > 5) {
    std::cerr << "Invalid number of arguments.\nUsage: " << argv[0]
              << "%s input_file output_dir suffix [--simple]\n";
    return 1;
  }

  std::string input_full_name = std::string(argv[1]);
  std::string output_folder_name = std::string(argv[2]);
  FLAGS_suffix = std::string(argv[3]);

  if (argc == 5) {
    if (strcmp(argv[4], "--simple") == 0) {
      FLAGS_simple = true;
    } else {
      std::cerr << "Invalid flags.\nUsage: " << argv[0]
                << " input_file output_dir suffix [--simple]\n";
      return 1;
    }
  }

  /* Set tournament size dynamically, if none provided. */
  if (FLAGS_tournament_size == -1) {
    FLAGS_tournament_size = FLAGS_pop_size / 20;
  }
  std::cout << "Tournament size: " << FLAGS_tournament_size << "\n";

  /* Parse filename. */
  std::string input_base_name =
      input_full_name.substr(input_full_name.find_last_of("/\\") + 1);
  std::string base_name = output_folder_name +
      input_base_name.substr(0, input_base_name.find_last_of('.'));

  /* Read project data from file. */
  std::unique_ptr<Project> project =
      std::move(ProjectReader::Read(input_full_name));
  if (project == nullptr) {
    std::cerr << "Invalid input file format.\n";
    return 1;
  }
  std::cout << "Tasks: " << project->size() << "\n";

  /* Project solution output: */
  std::string output_file_name = base_name;
  if (!FLAGS_suffix.empty()) {
    output_file_name += "." + FLAGS_suffix;
  }
  output_file_name += ".sol";
  std::ofstream output_file(output_file_name);

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
  std::ofstream best_file(best_file_name);

  /* Run the algorithm. */
  if (FLAGS_simple) {
    SolveAndOutput<SimpleSchedule>(stat_file_name, output_file, best_file,
                                   project.get());
  } else {
    SolveAndOutput<PrioSchedule>(stat_file_name, output_file, best_file,
                                 project.get());
  }

  return 0;
}
