#ifndef MS_RCPSP_VISUALIZATION_PALLETIZER_H_
#define MS_RCPSP_VISUALIZATION_PALLETIZER_H_

#include <tuple>

class Palletizer {
 public:
  Palletizer() : hue_(kSeed) {}
  Palletizer(double seed) : hue_(seed) {}

  std::tuple<double, double, double> GenerateColor();

 private:
  std::tuple<double, double, double> HSVToRGB(double h, double s, double v);

  double hue_;

  const double kPhi = 0.618033988749895;
  const double kSeed = 0.127878832961928;
  const double kSaturation = 0.5;
  const double kValue = 0.95;
};

#endif  // MS_RCPSP_VISUALIZATION_PALLETIZER_H_
