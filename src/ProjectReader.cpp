#include "../include/ProjectReader.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "../include/Project.h"

namespace SchedulingProblem {

bool ProjectReader::read(const std::string &filename) {
  int n, id, dur;
  size_t res_count, ndep, nres;
  int* dep;
  int* res;
  std::ifstream infile(filename);
  std::string line;
  std::smatch match;
  std::regex pattern("Tasks:\\s+(\\d+)");
  while (std::getline(infile, line) &&
         !std::regex_search(line, match, pattern)) {}
  if (match.empty()) return false;
  n = stoi(match[1]);
  pattern = "Resources:\\s+(\\d+)";
  if (!std::getline(infile, line) ||
      !std::regex_search(line, match, pattern)) return false;
  res_count = stoull(match[1]);

  for (int i = 0; i < 4; ++i) {
    if (!std::getline(infile, line)) return false;
  }

  Task** tasks = new Task*[n];
  int* res_id = new int[res_count];
  double* res_sal = new double[res_count];
  std::vector<std::map<int, int>> skills(res_count);

  pattern = "(\\d+)\\s+([\\d\\.]+)\\b";
  std::regex skill_pattern("Q(\\d+)\\:\\s*(\\d+)");
  for (size_t i = 0; i < res_count; i++) {
    if (!std::getline(infile, line) ||
        !std::regex_search(line, match, pattern)) return false;
    res_id[i] = stoi(match[1]);
    res_sal[i] = stof(match[2]);
    line = match.suffix();
    while (std::regex_search(line, match, skill_pattern)) {
      skills[i][stoi(match[1])] = stoi(match[2]);
      line = match.suffix();
    }
  }

  for (int i = 0; i < 2; ++i) {
    if (!std::getline(infile, line)) return false;
  }

  pattern = "(\\d+)\\s+(\\d+)\\s+Q(\\d+)\\:\\s+(\\d+)";
  std::regex dep_pattern("\\b(\\d+)\\b");
  int skill_id, skill_level;
  std::map<int, int> inv_task_id;
  for (int i = 0; i < n; i++) {
    if (!std::getline(infile, line) ||
        !std::regex_search(line, match, pattern)) return false;
    id = stoi(match[1]);
    inv_task_id[id] = i;
    dur = stoi(match[2]);
    skill_id = stoi(match[3]);
    skill_level = stoi(match[4]);
    std::vector<int> resources;
    for (size_t j = 0; j < res_count; ++j) {
      if (skills[j].count(skill_id) && skills[j][skill_id] >= skill_level) {
        resources.push_back(j);
      }
    }
    res = new int[nres = resources.size()];
    std::copy(resources.begin(), resources.end(), res);

    std::vector<int> dependencies;
    line = match.suffix();
    while (std::regex_search(line, match, dep_pattern)) {
      dependencies.push_back(inv_task_id[stoi(match[1])]);
      line = match.suffix();
    }
    dep = new int[ndep = dependencies.size()];
    std::copy(dependencies.begin(), dependencies.end(), dep);

    // increment duration to match solutions
    tasks[i] = new Task(id, dur + 1, dep, res, ndep, nres);
  }
  Project::create(n, tasks, res_count, res_id, res_sal);
  return true;
}

};  // namespace SchedulingProblem
