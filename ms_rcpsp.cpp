/**
 * Example of library usage. Reads project from file and finds a suboptimal
 * feasible schedule.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "gflags/gflags.h"

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

// Common flags
DEFINE_string(algorithm, "ea", "Search method (ea, ts or sa)");
DEFINE_uint32(iters, 500, "Number of iterations");
// EA flags
DEFINE_uint64(pop_size, 200, "Size of the population in EA");
DEFINE_double(crossover, 0.5, "Crossover probability");
DEFINE_bool(lax, false, "Use LAX crossover");
DEFINE_double(mutation, 0.01, "Mutation probability");
DEFINE_uint64(tournament_size, 0, "Tournament size");
DEFINE_bool(remove_clones, true, "Remove clones from population in EA");
// TS flags
DEFINE_uint32(list_size, 100, "Tabu list size in TS");
DEFINE_uint32(neighbours, 100, "Number of neighbours in TS");
// SA flags
DEFINE_double(temp, 1000, "Initial temperature in SA");
DEFINE_double(eps, 1e-5, "Lowest temperature in SA");
// Misc flags
DEFINE_string(suffix, "", "Suffix for output filename");
DEFINE_bool(output_stat, true, "Output iteration stats to .stat file");
DEFINE_bool(simple, false, "Use SimpleSchedule representation");

using namespace SchedulingProblem;
using namespace Solutions;
using namespace Solutions::EvolutionaryAlgorithm;

template <class T>
std::unique_ptr<Population<T>> BuildPopulation(size_t pop_size,
                                               Project* project) {
  std::vector<std::unique_ptr<T>> specimen;
  specimen.reserve(pop_size);
  for (size_t i = 0; i < pop_size; ++i) {
    specimen.push_back(std::make_unique<T>(project));
  }
  return std::make_unique<Population<T>>(std::move(specimen));
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
  double mut_prob = 1.0 / project->size();
  if (mut_prob < FLAGS_mutation) {
    mut_prob = FLAGS_mutation;
  }
  std::unique_ptr<Mutator<T>> mut =
      std::make_unique<UniformMutator<T>>(mut_prob);
  std::unique_ptr<Population<T>> pop =
      std::move(BuildPopulation<T>(FLAGS_pop_size, project));
  std::unique_ptr<Algorithm<T>> algo = nullptr;
  if (FLAGS_algorithm == "ea") {
    algo = std::make_unique<GeneticAlgorithm<T>>(std::move(pop),
                                                 std::move(sel),
                                                 std::move(cross),
                                                 std::move(mut),
                                                 FLAGS_iters,
                                                 FLAGS_remove_clones);
  } else if (FLAGS_algorithm == "sa") {
    algo = std::make_unique<SimulatedAnnealing<T>>(T(project),
                                                   FLAGS_iters,
                                                   FLAGS_temp,
                                                   mut_prob,
                                                   FLAGS_eps);
  } else if (FLAGS_algorithm == "ts") {
    algo = std::make_unique<TabuSearch<T>>(T(project),
                                           FLAGS_iters,
                                           FLAGS_neighbours,
                                           FLAGS_list_size,
                                           mut_prob);
  }
  std::unique_ptr<T> sch = nullptr;
  if (FLAGS_output_stat) {
    std::ofstream stat_file(stat_file_name);
    sch = std::move(algo->Optimize(stat_file));
  } else {
    sch = std::move(algo->Optimize());
  }
  // Force fitness computation to set start dates properly.
  sch->Fitness();
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
  best_file << sch->Fitness();
}

const char *kFilename = "main.cpp";

int main(int argc, char* argv[]) {
  std::ostringstream usage;
  usage << "Run chosen metaheuristic for scheduling problem:\n\n"
        << argv[0] << " def_file output_folder [FLAGS]\n"
        << "def_file       Project definition file\n"
        << "output_folder  Folder where output files are to be stored\n"
        << "               (MUST end with folder separator)";
  gflags::SetUsageMessage(usage.str());

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (argc != 3) {
    gflags::ShowUsageWithFlags(__FILE__);
    return 1;
  }

  std::transform(FLAGS_algorithm.begin(), FLAGS_algorithm.end(),
                 FLAGS_algorithm.begin(), ::tolower);
  if (FLAGS_algorithm != "ea" && FLAGS_algorithm != "ts" &&
      FLAGS_algorithm != "sa") {
    gflags::ShowUsageWithFlags(__FILE__);
    return 1;
  }

  std::string input_full_name = std::string(argv[1]);
  std::string output_folder_name = std::string(argv[2]);

  /* Set tournament size dynamically, if none provided. */
  if (FLAGS_tournament_size == 0) {
    FLAGS_tournament_size = FLAGS_pop_size / 20;
  }
  std::cout << "Tournament size: " << FLAGS_tournament_size << "\n";

  /* Parse filename. */
  std::string input_base_name =
      input_full_name.substr(input_full_name.find_last_of("/\\") + 1);
  std::string base_name = output_folder_name +
      input_base_name.substr(0, input_base_name.find_last_of('.'));

  /* Read project data from file. */
  std::ifstream project_stream(input_full_name);
  std::unique_ptr<Project> project =
      std::move(ProjectReader::Read(project_stream));
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
