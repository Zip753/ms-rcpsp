#include "visualizer.h"

#include <regex>

#include "../include/ProjectReader.h"
#include "renderer.h"

std::pair<bool, std::string> Visualizer::Visualize(std::istream& def,
                                                   std::istream& sol,
                                                   std::ostream& vis) {
  std::unique_ptr<SchedulingProblem::Project> project =
      SchedulingProblem::ProjectReader::Read(def);

  if (project == nullptr) { return {false, "Wrong .def format"}; }

  std::map<int, bool> is_critical = BuildCriticalPaths(project.get());

  // Map task ID to duration
  std::map<int, int> duration;
  for (size_t i = 0; i < project->size(); ++i) {
    duration[project->task(i).id()] = project->task(i).duration();
  }

  // Read first line with headers
  std::string line;
  if (!std::getline(sol, line)) return {false, "Missing .sol header"};
  // Read task assignments
  std::map<int, std::vector<assignment>> assignments;
  std::smatch match;
  std::regex pattern;
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
      int finish_time = start_time + duration[task_id] - 1;
      assignments[resource_id].push_back({task_id, start_time, finish_time,
                                          is_critical[task_id]});
      line = match.suffix();
    }
  }

  vis << renderer_->GetHTML(assignments);

  return {true, "OK"};
}

std::map<int, bool> Visualizer::BuildCriticalPaths(
    SchedulingProblem::Project* project) {

  std::vector<int> min_finish_time(project->size(), -1);
  int max_min_finish_time = -1;
  for (size_t i = 0; i < project->size(); ++i) {
    int finish = ComputeFinishTime(i, project, &min_finish_time);
    if (max_min_finish_time < finish) {
      max_min_finish_time = finish;
    }
  }

  std::map<int, bool> is_critical;
  for (size_t i = 0; i < project->size(); ++i) {
    if (min_finish_time[i] == max_min_finish_time) {
      CheckCriticalPath(i, project, &is_critical, min_finish_time);
    }
  }

  return is_critical;
}

bool Visualizer::CheckCriticalPath(size_t task_idx,
                                   SchedulingProblem::Project* project,
                                   std::map<int, bool>* is_critical,
                                   const std::vector<int> &min_finish_time) {
  const SchedulingProblem::Task &task = project->task(task_idx);
  
  if (is_critical->count(task.id()) > 0) {
    return is_critical->at(task.id());
  }
  
  if (task.num_dependencies() == 0) {
    is_critical->insert({task.id(), true});
    return true;
  }
  is_critical->insert({task.id(), false});

  int task_finish_time = min_finish_time.at(task_idx);
  for (size_t i = 0; i < task.num_dependencies(); ++i) {
    size_t dep_idx = task.dependency(i);
    if (min_finish_time.at(dep_idx) == task_finish_time - task.duration() - 1 &&
        CheckCriticalPath(dep_idx, project, is_critical, min_finish_time)) {
      is_critical->at(task.id()) = true;
    }
  }

  return is_critical->at(task.id());
}

int Visualizer::ComputeFinishTime(size_t task_idx,
                                  SchedulingProblem::Project* project,
                                  std::vector<int>* min_finish_time) {
  const SchedulingProblem::Task &task = project->task(task_idx);
  int &task_finish_time = min_finish_time->at(task_idx);

  if (task_finish_time != -1) { return task_finish_time; }
  
  task_finish_time = task.duration();
  for (size_t i = 0; i < task.num_dependencies(); ++i) {
    size_t dep_idx = task.dependency(i);
    ComputeFinishTime(dep_idx, project, min_finish_time);
    if (task_finish_time <= min_finish_time->at(dep_idx) + task.duration()) {
      task_finish_time = min_finish_time->at(dep_idx) + task.duration() + 1;
    }
  }

  return task_finish_time;
}
