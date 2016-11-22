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
      stream << "Resource index out of boundaries (task ID: ";
      stream << s.task(i).id();
      stream << ", resource index: ";
      stream << s.capable_resource_idx(i);
      stream << ", capable resources: ";
      stream << s.task(i).num_capable_resources();
      stream << ").";
      return std::make_pair(false, stream.str());
    }
    // Check task dependencies.
    for (size_t j = 0; j < s.task(i).num_dependencies(); ++j) {
      size_t dep_idx = s.task(i).dependency(j);
      if (s.finish_time(dep_idx) >= s.start(i)) {
        stream << "Task dependency not met (task #";
        stream << s.task(i).id();
        stream << " start time: ";
        stream << s.start(i);
        stream << ", task #";
        stream << s.task(dep_idx).id();
        stream << " finish time: ";
        stream << s.finish_time(dep_idx);
        stream << ").";
        return std::make_pair(false, stream.str());
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
      return s.start(a) < s.start(b) ||
          (s.start(a) == s.start(b) && s.finish_time(a) < s.finish_time(b));
    });

    for (size_t i = 0; i < tasks.size() - 1; ++i) {
      if (s.finish_time(tasks[i]) >= s.start(tasks[i + 1])) {
        stream << "Resource #";
        stream << res_id;
        stream << " has conflicting assignments (task #";
        stream << s.task(tasks[i]).id();
        stream << " finish time: ";
        stream << s.finish_time(tasks[i]);
        stream << ", task #";
        stream << s.task(tasks[i + 1]).id();
        stream << " start time: ";
        stream << s.start(tasks[i + 1]);
        stream << ").";
        return std::make_pair(false, stream.str());
      }
    }
  }

  return std::make_pair(true, "OK");
}

};  // namespace SchedulingProblem
