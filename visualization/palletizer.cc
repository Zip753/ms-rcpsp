#include "palletizer.h"

#include <cmath>
#include <iomanip>
#include <ostream>

std::tuple<double, double, double> Palletizer::GenerateColor() {
  hue_ += kPhi;
  hue_ -= floor(hue_);  // leave only fractional part
  return HSVToRGB(hue_, kSaturation, kValue);
}

std::tuple<double, double, double> Palletizer::HSVToRGB(double h,
                                                        double s,
                                                        double v) {
  size_t remainder = static_cast<size_t>(floor(h * 6));
  if (remainder == 6) remainder = 0;
  double f = h * 6 - remainder;
  double p = v * (1 - s);
  double q = v * (1 - f * s);
  double t = v * (1 - (1 - f) * s);
  switch (remainder) {
    case 0:
      return std::make_tuple(v, t, p);
    case 1:
      return std::make_tuple(q, v, p);
    case 2:
      return std::make_tuple(p, v, t);
    case 3:
      return std::make_tuple(p, q, v);
    case 4:
      return std::make_tuple(t, p, v);
    case 5:
      return std::make_tuple(v, p, q);
    default:
      throw new std::out_of_range("Hue value must be in [0, 1]");
  }
}
