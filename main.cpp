#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

float hit_sphere(const point3 &center, float radius, const ray &r) {
  /*
  x^2 + y^2 + z^2 = R^2
  Sphere Center move to (Sx, Sy, Sz)
  (Sx - x)^2 + (Sy - y)^2 + (Sz - z)^2 = R^2
  Vector from P(x,y,z) to S(Sx, Sy, Sz) (P-S)
  (S-P)^2 = R^2
  P is a function of t based on the ray
  (S - P(t))^2 = R^2
  P(t) = C(center) + tD(direction)
  (S - (C + tD))^2 = R^2
  (td + C - S)^2 = R^2
  tD^2 + 2tD(C-S) + (C-S)^2 - R^2 = 0
  A = d^2, B = 2D(C-S), C = (C-S)^2 - R^2
  B^2 - 4AC > 0 -> hit
  */
  point3 oc = r.origin() - center;
  auto a = dot(r.direction(), r.direction());
  auto b = 2.0 * dot(oc, r.direction());
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  // return (discriminant > 0);
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}

color3 ray_color(const ray &r) {
  auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
  if (t > 0.0) {
    point3 N = unit_vector(r.at(t) - point3(0, 0, -1));
    return 0.5 * color3(N.x() + 1, N.y() + 1, N.z() + 1);
  } else {
    point3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color3(1.0, 1.0, 1.0) + a * color3(0.5, 0.7, 1.0);
  }
}

int main() {
  auto aspect_ratio = 16.0 / 9.0;
  int img_w = 400;

  int img_h = static_cast<int>(img_w / aspect_ratio);
  img_h = (img_h < 1) ? 1 : img_h;

  // camera position

  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (float(img_w) / img_h);
  auto camera_center = point3(0, 0, 0);

  auto viewpoint_u = point3(viewport_width, 0, 0);
  auto viewpoint_v = point3(0, -viewport_height, 0);

  auto pixel_du = viewpoint_u / float(img_w);
  auto pixel_dv = viewpoint_v / float(img_h);

  auto viewport_lower_left_corner = camera_center - viewpoint_u / 2 -
                                    viewpoint_v / 2 -
                                    point3(0, 0, focal_length);
  auto pixel_00 = viewport_lower_left_corner + 0.5 * (pixel_du + pixel_dv);

  // Render

  std::cout << "P3\n" << img_w << " " << img_h << "\n255\n";
  for (int i = 0; i < img_h; i++) {
    std::clog << "\rScanlines remaining: " << img_h - i << std::flush;
    for (int j = 0; j < img_w; j++) {
      auto pixel_center = pixel_00 + j * pixel_du + i * pixel_dv;
      auto ray_dir = pixel_center - camera_center;
      ray r(camera_center, ray_dir);

      color3 pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                 \n";
}