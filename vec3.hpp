#ifndef VEC #_HPP
#define VEC #_HPP

#include <cmath>
#include <iostream>

template <typename T>
class vec3
{
public:
  float e[3];
  vec3() : e{0, 0, 0} {}
  vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

  float x() const { return e[0]; }
  float y() const { return e[1]; }
  float z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  float operator[](int i) const { return e[i]; }
  float &operator[](int i) { return e[i]; }

  vec3 &operator+=(const vec3 &v)
  {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  vec3 &operator*=(const float t)
  {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }
  vec3 &operator/=(const float t)
  {
    return *this *= 1 / t;
  }

  float length() const
  {
    return sqrt(length_squared());
  }
  float length_squared() const
  {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }
};

struct PointTag
{
};
struct ColorTag
{
};

using point3 = vec3<PointTag>;

template <typename Tag>
inline std::ostream &operator<<(std::ostream &out, const vec3<Tag> &v)
{
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

template <typename Tag>
inline vec3<Tag> operator+(const vec3<Tag> &u, const vec3<Tag> &v)
{
  return vec3<Tag>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

template <typename Tag>
inline vec3<Tag> operator-(const vec3<Tag> &u, const vec3<Tag> &v)
{
  return vec3<Tag>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

template <typename Tag>
inline vec3<Tag> operator*(const vec3<Tag> &u, const vec3<Tag> &v)
{
  return vec3<Tag>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

template <typename Tag>
inline vec3<Tag> operator*(double t, const vec3<Tag> &v)
{
  return vec3<Tag>(t * v.e[0], t * v.e[1], t * v.e[2]);
}

template <typename Tag>
inline vec3<Tag> operator*(const vec3<Tag> &v, double t)
{
  return t * v;
}
#endif