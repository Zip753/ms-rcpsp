#ifndef MS_RCPSP_VISUALIZATION_VISUALIZER_H_
#define MS_RCPSP_VISUALIZATION_VISUALIZER_H_

#include <iostream>
#include <map>
#include <vector>

class Renderer;

class Visualizer {
 public:
  Visualizer(Renderer *renderer_) : renderer_(renderer_) {}

  struct assignment {
    int task_id;
    int start_time;
    int finish_time;
    bool critical;
  };

  typedef std::map<int, std::vector<assignment>> assignments_map;
  typedef std::multimap<int, assignment*> schedule_map;

  std::pair<bool, std::string> Visualize(std::istream& def,
                                         std::istream& sol,
                                         std::ostream& vis);

 private:
  Renderer* renderer_;

  void BuildCriticalPaths(assignments_map* assignments);

  bool CheckCriticalPath(assignment *assignment, schedule_map* schedule);
};

#endif  // MS_RCPSP_VISUALIZATION_VISUALIZER_H_
