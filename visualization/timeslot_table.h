#ifndef MS_RCPSP_VISUALIZATION_TIMESLOT_TABLE_H_
#define MS_RCPSP_VISUALIZATION_TIMESLOT_TABLE_H_

#include "renderer.h"

#include <string>

class TimeslotTable final : public Renderer {
 public:
  TimeslotTable(Palletizer* palletizer_) : Renderer(palletizer_) {}

  std::string GetHTML(Visualizer::assignments_map &assignments) override;

 private:
  int GetMaxFinishTime(Visualizer::assignments_map &assignments);
};

#endif  // MS_RCPSP_VISUALIZATION_TIMESLOT_TABLE_H_
