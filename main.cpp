#include <iostream>
#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"

color3 ray_color(const ray &r)
{
  // return color3(0, 0, 0);
  point3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color3(1.0, 1.0, 1.0) + t * color3(0.5, 0.7, 1.0);
}

int main()
{
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

  auto viewport_lower_left_corner = camera_center - viewpoint_u / 2 - viewpoint_v / 2 - point3(0, 0, focal_length);
  auto pixel_00 = viewport_lower_left_corner + 0.5 * (pixel_du + pixel_dv);

  // Render

  std::cout << "P3\n"
            << img_w << " " << img_h << "\n255\n";
  for (int i = 0; i < img_h; i++)
  {
    std::clog << "\rScanlines remaining: " << img_h - i << std::flush;
    for (int j = 0; j < img_w; j++)
    {
      auto pixel_center = pixel_00 + j * pixel_du + i * pixel_dv;
      auto ray_dir = pixel_center - camera_center;
      ray r(camera_center, ray_dir);

      color3 pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                 \n";
}