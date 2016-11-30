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

std::unique_ptr<Project> ProjectReader::Read(std::istream &infile) {
  std::string line;
  std::smatch match;

  // Read number of tasks
  std::regex pattern("Tasks:\\s+(\\d+)");
  while (std::getline(infile, line) &&
         !std::regex_search(line, match, pattern)) {}
  if (match.empty()) return nullptr;
  size_t task_count = stoul(match[1]);

  // Read number of resources
  pattern = "Resources:\\s+(\\d+)";
  if (!std::getline(infile, line) ||
      !std::regex_search(line, match, pattern)) return nullptr;
  size_t res_count = stoull(match[1]);

  // Skip 4 lines
  for (size_t i = 0; i < 4; ++i) {
    if (!std::getline(infile, line)) return nullptr;
  }

  std::vector<Task> tasks;
  tasks.reserve(task_count);
  std::vector<Resource> res;
  res.reserve(res_count);
  std::vector<std::map<int, int>> skills(res_count);

  // Read skills
  pattern = "(\\d+)\\s+([\\d\\.]+)\\b";
  std::regex skill_pattern("Q(\\d+)\\:\\s*(\\d+)");
  for (size_t i = 0; i < res_count; i++) {
    if (!std::getline(infile, line) ||
        !std::regex_search(line, match, pattern)) return nullptr;
    int res_id = stoi(match[1]);
    double res_sal = stod(match[2]);
    res.emplace_back(res_id, res_sal);
    line = match.suffix();
    while (std::regex_search(line, match, skill_pattern)) {
      skills[i][stoi(match[1])] = stoi(match[2]);
      line = match.suffix();
    }
  }

  // Skip 2 lines
  for (size_t i = 0; i < 2; ++i) {
    if (!std::getline(infile, line)) return nullptr;
  }

  // Read tasks
  pattern = "(\\d+)\\s+(\\d+)\\s+Q(\\d+)\\:\\s+(\\d+)";
  std::regex dep_pattern("\\b(\\d+)\\b");
  std::map<int, size_t> inv_task_id;
  for (size_t i = 0; i < task_count; i++) {
    if (!std::getline(infile, line) ||
        !std::regex_search(line, match, pattern)) return nullptr;
    int id = stoi(match[1]);
    inv_task_id[id] = i;
    int dur = stoi(match[2]);
    int skill_id = stoi(match[3]);
    int skill_level = stoi(match[4]);

    // Find all capable resources
    std::vector<size_t> resources;
    for (size_t j = 0; j < res_count; ++j) {
      if (skills[j].count(skill_id) && skills[j][skill_id] >= skill_level) {
        resources.push_back(j);
      }
    }

    // Find dependencies indexes
    std::vector<size_t> dependencies;
    line = match.suffix();
    while (std::regex_search(line, match, dep_pattern)) {
      dependencies.push_back(inv_task_id[stoul(match[1])]);
      line = match.suffix();
    }

    tasks.emplace_back(id, dur, dependencies, resources);
  }

  return std::make_unique<Project>(tasks, res);
}

};  // namespace SchedulingProblem
