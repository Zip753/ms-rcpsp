#include "renderer.h"

#include <cmath>
#include <iomanip>

std::string Renderer::GetColor() {
  double r, g, b;
  std::tie(r, g, b) = palletizer_->GenerateColor();
  size_t red   = static_cast<size_t>(floor(r * 255));
  size_t green = static_cast<size_t>(floor(g * 255));
  size_t blue  = static_cast<size_t>(floor(b * 255));
  std::ostringstream color("'#", std::ostringstream::ate);
  color << std::hex << std::setfill('0')
        << std::setw(2) << red
        << std::setw(2) << green
        << std::setw(2) << blue
        << "'";
  return color.str();
}
