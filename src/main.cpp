#include "rtweekend.hpp"
#include "color.hpp"
// #include "vec3.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include <iostream>



double clamp(double val, double min, double max) {
  return std::max(min, std::min(max, val));
}

color ray_color(const ray&r, const hittable& world) {
  hit_record rec;
  // if (world.hit(r, 0, infinity, rec)) {
  if (world.hit(r, interval(0, infinity), rec)) {
    // return 0.5 * (rec.normal + color(1,1,1));
    double depth = clamp(rec.t, -5.0, 5.0);
    return (5.0 - depth) * color(1.0, 1.0, 1.0) + depth * color(0.0, 0.0, 0.0);
  }
  // Background
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5*(unit_direction.y() + 1.0);
  return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main () {
  auto aspect_ratio = 16.0 / 9.0;
  int img_width = 400;

  int img_height = static_cast<int>(img_width / aspect_ratio);
  img_height = (img_height > 0) ? img_height : 1;

  // World

  hittable_list world;

  world.add(make_shared<sphere>(point3(0,0,-3), 2));
  // world.add(make_shared<sphere>(point3(1,0,-1), 0.15));
  // world.add(make_shared<sphere>(point3(-1,-0.1,-1), 0.35));
  // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

  // Camera

  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (static_cast<double>(img_width)/img_height);
  auto camera_center = point3(0, 0, 0);

  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  auto pixel_delta_u = viewport_u / (img_width - 1);
  auto pixel_delta_v = viewport_v / (img_height - 1);

  auto viewport_upper_left = camera_center - viewport_u/2 - viewport_v/2 - vec3(0, 0, focal_length);
  auto pixel00_loc = viewport_upper_left;

  // Render
  std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

  for (int j = 0; j < img_height; j++) {
    std::clog << "\rScanlines remaining: " << img_height - j << ' ' << std::flush;
    for (int i = 0; i < img_width; i++) {
      auto pixel_loc = pixel00_loc + pixel_delta_u * i + pixel_delta_v * j;
      auto ray_direction = pixel_loc - camera_center;
      ray r(camera_center, ray_direction);
      color pixel_color = ray_color(r, world);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                 \n";
}