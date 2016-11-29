#ifndef MS_RCPSP_VISUALIZATION_VISUALIZER_H_
#define MS_RCPSP_VISUALIZATION_VISUALIZER_H_

#include <iostream>
#include <map>
#include <vector>
#include "../include/Project.h"

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

  std::pair<bool, std::string> Visualize(std::istream& def,
                                         std::istream& sol,
                                         std::ostream& vis);

 private:
  Renderer* renderer_;

  std::map<int, bool> BuildCriticalPaths(SchedulingProblem::Project* project);

  int ComputeFinishTime(size_t task_idx, SchedulingProblem::Project* project,
                        std::vector<int>* min_finish_time);

  bool CheckCriticalPath(size_t task_idx, SchedulingProblem::Project* project,
                         std::map<int, bool>* is_critical,
                         const std::vector<int> &min_finish_time);
};

#endif  // MS_RCPSP_VISUALIZATION_VISUALIZER_H_
