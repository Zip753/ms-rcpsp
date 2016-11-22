#ifndef MS_RCPSP_VISUALIZATION_RENDERER_H_
#define MS_RCPSP_VISUALIZATION_RENDERER_H_

#include "palletizer.h"
#include "visualizer.h"

class Renderer {
 public:
  Renderer(Palletizer *palletizer_) : palletizer_(palletizer_) {}

  virtual std::string GetHTML(Visualizer::assignments_map &assignments) = 0;

 private:
  Palletizer* palletizer_;

 protected:
  std::string GetColor();
};

#endif  // MS_RCPSP_VISUALIZATION_RENDERER_H_
