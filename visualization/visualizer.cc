#include "visualizer.h"

#include <regex>

#include "renderer.h"

std::pair<bool, std::string> Visualizer::Visualize(std::istream& def,
                                                   std::istream& sol,
                                                   std::ostream& vis) {
  std::string line;
  do {
    if (!std::getline(def, line)) return {false, "Wrong .def format"};
  } while (line != "TaskID \t Duration \t Skill \t Predecessor IDs ");

  // Read task IDs and durations
  std::smatch match;
  std::regex pattern("^(\\d+)\\s+(\\d+)");
  std::map<int, int> duration;
  while (std::getline(def, line)) {
    if (!std::regex_search(line, match, pattern)) break;
    int task_id = std::stoi(match[1]);
    int task_duration = std::stoi(match[2]);
    duration[task_id] = task_duration;
  }

  // Read first line with headers
  if (!std::getline(sol, line)) return {false, "Missing .sol header"};
  // Read task assignments
  std::map<int, std::vector<assignment>> assignments;
  while (std::getline(sol, line)) {
    // Read start time
    pattern = "(\\d+)";
    if (!std::regex_search(line, match, pattern)) {
      return {false, "Missing start time"};
    }
    int start_time = std::stoi(match[1]);
    // Read assignments
    line = match.suffix();
    pattern = "(\\d+)-(\\d+)";
    while (std::regex_search(line, match, pattern)) {
      int resource_id = stoi(match[1]);
      int task_id = stoi(match[2]);
      int finish_time = start_time + duration[task_id];
      assignments[resource_id].push_back({task_id, start_time, finish_time,
                                          false});
      line = match.suffix();
    }
  }

  BuildCriticalPaths(&assignments);

  vis << renderer_->GetHTML(assignments);

  return {true, "OK"};
}

void Visualizer::BuildCriticalPaths(assignments_map* assignments) {
  // Map finish time to references to assignments
  std::multimap<int, assignment*> schedule;

  int max_finish = 0;
  for (auto& res : *assignments) {
    for (auto& a : res.second) {
      schedule.insert({a.finish_time, &a});
      if (max_finish < a.finish_time)
        max_finish = a.finish_time;
    }
  }

  auto range = schedule.equal_range(max_finish);
  for (auto& a = range.first; a != range.second; ++a) {
    CheckCriticalPath(a->second, &schedule);
  }
}

bool Visualizer::CheckCriticalPath(assignment *assignment,
                                   schedule_map *schedule) {
  if (assignment->critical || assignment->start_time == 1) {
    assignment->critical = true;
    return true;
  }
  auto range = schedule->equal_range(assignment->start_time - 1);
  for (auto& a = range.first; a != range.second; ++a) {
    if (CheckCriticalPath(a->second, schedule)) {
      assignment->critical = true;
    }
  }
  schedule->erase(range.first, range.second);
  return assignment->critical;
}
