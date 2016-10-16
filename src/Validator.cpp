#include "../include/Validator.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../include/Project.h"
#include "../include/Schedule.h"

namespace SchedulingProblem {

std::pair<bool, std::string> Validator::validate(const Schedule& s) {
  std::ostringstream stream;
  for (int i = 0; i < Project::size(); ++i) {
    // Check resource indices.
    if (s.ires[i] < 0 || s.ires[i] >= s.max_res_count(i)) {
      stream << "Resource index out of boundaries (task ID: ";
      stream << s.tasks[i]->id;
      stream << ", resource index: ";
      stream << s.ires[i];
      stream << ", capable resources: ";
      stream << s.max_res_count(i);
      stream << ").";
      return std::make_pair(false, stream.str());
    }
    // Check task dependencies.
    for (int j = 0; j < s.tasks[i]->dep_size(); ++j) {
      int dep_id = s.tasks[i]->dep[j];
      if (s.finish_time(dep_id) > s.start[i]) {
        stream << "Task dependency not met (task #";
        stream << s.tasks[i]->id;
        stream << " start time: ";
        stream << s.start[i];
        stream << ", task #";
        stream << s.tasks[dep_id]->id;
        stream << " finish time: ";
        stream << s.finish_time(dep_id);
        stream << ").";
        return std::make_pair(false, stream.str());
      }
    }
  }

  // Check resource assignment conflicts.
  std::map<int, std::vector<int>> res_tasks;
  for (int i = 0; i < Project::size(); ++i) {
    int res_id = Project::get_res_id(s.resource(i));
    res_tasks[res_id].push_back(i);
  }

  for (auto& res : res_tasks) {
    int res_id = res.first;
    std::vector<int>& tasks = res.second;
    std::sort(tasks.begin(), tasks.end(), [&](int a, int b) {
      return s.start[a] < s.start[b] ||
          (s.start[a] == s.start[b] && s.finish_time(a) < s.finish_time(b));
    });

    for (size_t i = 0; i < tasks.size() - 1; ++i) {
      if (s.finish_time(tasks[i]) > s.start[tasks[i + 1]]) {
        stream << "Resource #";
        stream << res_id;
        stream << " has conflicting assignments (task #";
        stream << s.tasks[tasks[i]]->id;
        stream << " finish time: ";
        stream << s.finish_time(tasks[i]);
        stream << ", task #";
        stream << s.tasks[tasks[i + 1]]->id;
        stream << " start time: ";
        stream << s.start[tasks[i + 1]];
        stream << ").";
        return std::make_pair(false, stream.str());
      }
    }
  }

  return std::make_pair(true, "OK");
}

};  // namespace SchedulingProblem
