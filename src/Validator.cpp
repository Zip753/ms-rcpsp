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

std::pair<bool, std::string> Validator::Validate(const Schedule &s) {
  std::ostringstream stream;
  for (size_t i = 0; i < s.size(); ++i) {
    // Check start time
    if (s.start(i) < 0) {
      stream << "Negative start time (task ID: " << s.task(i).id()
             << ", start time: " << s.start(i) << ").";
      return {false, stream.str()};
    }
    // Check resource indices.
    if (s.capable_resource_idx(i) < 0 ||
        s.capable_resource_idx(i) >= s.task(i).num_capable_resources()) {
      stream << "Resource index out of boundaries (task ID: " << s.task(i).id()
             << ", resource index: " << s.capable_resource_idx(i)
             << ", capable resources: " << s.task(i).num_capable_resources()
             << ").";
      return {false, stream.str()};
    }
    // Check task dependencies.
    for (size_t j = 0; j < s.task(i).num_dependencies(); ++j) {
      size_t dep_idx = s.task(i).dependency(j);
      if (s.finish_time(dep_idx) >= s.start(i)) {
        stream << "Task dependency not met (task #" << s.task(i).id()
               << " start time: " << s.start(i)
               << ", task #" << s.task(dep_idx).id()
               << " finish time: " << s.finish_time(dep_idx) << ").";
        return {false, stream.str()};
      }
    }
  }

  // Check resource assignment conflicts.
  std::map<int, std::vector<size_t>> res_tasks;
  for (size_t i = 0; i < s.size(); ++i) {
    int res_id = s.resource(i).id();
    res_tasks[res_id].push_back(i);
  }

  for (auto& res : res_tasks) {
    int res_id = res.first;
    std::vector<size_t>& tasks = res.second;
    std::sort(tasks.begin(), tasks.end(), [&](size_t a, size_t b) {
      return std::make_pair(s.start(a), s.finish_time(a)) <
             std::make_pair(s.start(b), s.finish_time(b));
    });

    for (size_t i = 0; i < tasks.size() - 1; ++i) {
      if (s.finish_time(tasks[i]) >= s.start(tasks[i + 1])) {
        stream << "Resource #" << res_id << " has conflicting assignments "
               << "(task #" << s.task(tasks[i]).id()
               << " finish time: " << s.finish_time(tasks[i])
               << ", task #" << s.task(tasks[i + 1]).id()
               << " start time: " << s.start(tasks[i + 1]) << ").";
        return {false, stream.str()};
      }
    }
  }

  return {true, "OK"};
}

};  // namespace SchedulingProblem
