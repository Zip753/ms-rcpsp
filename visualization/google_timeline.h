#ifndef MS_RCPSP_VISUALIZATION_GOOGLE_TIMELINE_H_
#define MS_RCPSP_VISUALIZATION_GOOGLE_TIMELINE_H_

#include <string>

#include "renderer.h"

class GoogleTimeline final : public Renderer {
 public:
  GoogleTimeline(Palletizer* palletizer_, bool critical_)
      : Renderer(palletizer_, critical_) {}

  std::string GetHTML(const Visualizer::assignments_map &assignments) override;
};

#endif  // MS_RCPSP_VISUALIZATION_GOOGLE_TIMELINE_H_
