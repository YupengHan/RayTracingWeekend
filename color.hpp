#pragma once

#include "vec3.hpp"

using color3 = vec3<ColorTag>;

void write_color(std::ostream &out, const color3 &pixel_color) {
  out << static_cast<int>(255.999 * pixel_color.x()) << ' '
      << static_cast<int>(255.999 * pixel_color.y()) << ' '
      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}
