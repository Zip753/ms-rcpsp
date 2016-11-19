#include "../include/ScheduleWriter.h"

#include <list>
#include <map>

#include "../include/Schedule.h"

namespace SchedulingProblem {

void ScheduleWriter::Write(std::ostream &stream, const Schedule& s) {
  stream << "Hour \t Resource assignments (resource ID - task ID) \n";
  std::map<int, std::list<std::pair<int, int> > > timeline;
  for (size_t i = 0; i < s.size(); i++) {
    int st = s.start(i) + 1;
    int res = s.resource_id(s.resource(i));
    int task_id = s.task(i).id();

    if (timeline.count(st) == 0) {
      timeline[st] = std::list<std::pair<int, int> >();
    }
    timeline[st].push_back(std::make_pair(res, task_id));
  }
  for (auto it = timeline.begin(); it != timeline.end(); it++) {
    stream << it->first << " ";
    for (auto lit = it->second.begin(); lit != it->second.end(); lit++) {
      stream << lit->first << "-" << lit->second << " ";
    }
    stream << std::endl;
  }
}

};  // namespace SchedulingProblem
