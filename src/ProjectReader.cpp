#include "../include/ProjectReader.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

#include "../include/Project.h"

namespace SchedulingProblem {

std::unique_ptr<Project> ProjectReader::Read(const std::string &filename) {
  size_t n;
  int id, dur;
  size_t res_count;
  std::ifstream infile(filename);
  std::string line;
  std::smatch match;
  std::regex pattern("Tasks:\\s+(\\d+)");
  while (std::getline(infile, line) &&
         !std::regex_search(line, match, pattern)) {}
  if (match.empty()) return nullptr;
  n = stoul(match[1]);
  pattern = "Resources:\\s+(\\d+)";
  if (!std::getline(infile, line) ||
      !std::regex_search(line, match, pattern)) return nullptr;
  res_count = stoull(match[1]);

  for (size_t i = 0; i < 4; ++i) {
    if (!std::getline(infile, line)) return nullptr;
  }

  std::vector<Task> tasks;
  tasks.reserve(n);
  std::vector<int> res_id(res_count);
  std::vector<double> res_sal(res_count);
  std::vector<std::map<int, int>> skills(res_count);

  pattern = "(\\d+)\\s+([\\d\\.]+)\\b";
  std::regex skill_pattern("Q(\\d+)\\:\\s*(\\d+)");
  for (size_t i = 0; i < res_count; i++) {
    if (!std::getline(infile, line) ||
        !std::regex_search(line, match, pattern)) return nullptr;
    res_id[i] = stoi(match[1]);
    res_sal[i] = stof(match[2]);
    line = match.suffix();
    while (std::regex_search(line, match, skill_pattern)) {
      skills[i][stoi(match[1])] = stoi(match[2]);
      line = match.suffix();
    }
  }

  for (size_t i = 0; i < 2; ++i) {
    if (!std::getline(infile, line)) return nullptr;
  }

  pattern = "(\\d+)\\s+(\\d+)\\s+Q(\\d+)\\:\\s+(\\d+)";
  std::regex dep_pattern("\\b(\\d+)\\b");
  int skill_id, skill_level;
  std::map<int, size_t> inv_task_id;
  for (size_t i = 0; i < n; i++) {
    if (!std::getline(infile, line) ||
        !std::regex_search(line, match, pattern)) return nullptr;
    id = stoi(match[1]);
    inv_task_id[id] = i;
    dur = stoi(match[2]);
    skill_id = stoi(match[3]);
    skill_level = stoi(match[4]);
    std::vector<size_t> resources;
    for (size_t j = 0; j < res_count; ++j) {
      if (skills[j].count(skill_id) && skills[j][skill_id] >= skill_level) {
        resources.push_back(j);
      }
    }

    std::vector<size_t> dependencies;
    line = match.suffix();
    while (std::regex_search(line, match, dep_pattern)) {
      dependencies.push_back(inv_task_id[stoul(match[1])]);
      line = match.suffix();
    }

    if (i == 17) std::cout << resources.size() << std::endl;

    // increment duration_ to match solutions
    tasks.emplace_back(id, dur + 1, dependencies, resources);
  }
  std::unique_ptr<Project> project =
      std::make_unique<Project>(tasks, res_id, res_sal);
  return std::move(project);
}

};  // namespace SchedulingProblem
