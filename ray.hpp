#pragma once

#include "vec3.hpp"

class ray {
 public:
  ray() {}
  ray(const point3 &origin, const point3 &direction)
      : orig(origin), dir(direction) {}

  const point3 &origin() const { return orig; }
  const point3 &direction() const { return dir; }

  point3 at(float t) const { return orig + t * dir; }

 private:
  point3 orig;
  point3 dir;
};
