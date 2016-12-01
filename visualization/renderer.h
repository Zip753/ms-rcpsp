#ifndef MS_RCPSP_VISUALIZATION_RENDERER_H_
#define MS_RCPSP_VISUALIZATION_RENDERER_H_

#include "palletizer.h"
#include "visualizer.h"

class Renderer {
 public:
  Renderer(Palletizer *palletizer_, bool critical_)
      : palletizer_(palletizer_), critical_(critical_) {}

  virtual std::string GetHTML(
      const Visualizer::assignments_map &assignments) = 0;

 private:
  Palletizer* palletizer_;
  bool critical_;

 protected:
  std::string GetColor();
  inline bool critical() const { return critical_; }
};

#endif  // MS_RCPSP_VISUALIZATION_RENDERER_H_
