#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.hpp"

class interval {
  public:
    double min, max;
    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max) : min(min), max(max) {}
    bool contains(double x) const {
      return min <= x && x <= max;
    }
    bool surrounds(double x) const {
        return min < x && x < max;
    }
    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

const static interval empty = interval(+infinity, -infinity);
const static interval universe = interval(-infinity, +infinity);

#endif