#ifndef CAMERA_H
#define CAMERA_H
#include "rtweekend.hpp"
#include "interval.hpp"
#include "color.hpp"
#include "hittable.hpp"

#include <iostream>

class camera {
  public:
  /* Public Camera Parameters Here*/
  double aspect_ratio = 1; 
  int img_width = 100;
  int samples_per_pixel = 1;

  void render(const hittable& world) {
    initialize();
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
    for (int j = 0; j < img_height; j++) {
      std::clog << "\rScanlines remaining: " << img_height - j << ' ' << std::flush;
      for (int i = 0; i < img_width; i++) {
        color pixel_color(0,0,0);
        for (int sample = 0; sample < samples_per_pixel; ++sample) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world);
        }
        write_color(std::cout, pixel_color, samples_per_pixel);

        // auto pixel_loc = pixel00_loc + pixel_delta_u * i + pixel_delta_v * j;
        // auto ray_direction = pixel_loc - camera_center;
        // ray r(camera_center, ray_direction);
        // color pixel_color = ray_color(r, world);
        // write_color(std::cout, pixel_color);
      }
    }
    std::clog << "\rDone.                 \n";
  }
  private:
  /* Private Camera Parameters Here*/
    int img_height;
    point3 camera_center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
  void initialize() {
    img_height = static_cast<int>(img_width / aspect_ratio);
    img_height = (img_height < 1 ) ? 1 : img_height;

    camera_center = point3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(img_width)/img_height);

    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / (img_width - 1);
    pixel_delta_v = viewport_v / (img_height - 1);

    auto viewport_upper_left = camera_center - viewport_u/2 - viewport_v/2 - vec3(0, 0, focal_length);
    pixel00_loc = viewport_upper_left;
  }
  ray get_ray(int i, int j) const {
    // Get a randomly sampled camera ray for the pixel at location i,j.

    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = camera_center;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
  }

  vec3 pixel_sample_square() const {
    // Returns a random point in the square surrounding a pixel at the origin.
    auto px = -0.5 + random_double();
    auto py = -0.5 + random_double();
    return (px * pixel_delta_u) + (py * pixel_delta_v);
  }

  color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
      return 0.5 * (rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    
    // hit_record rec;

    // if (world.hit(r, interval(0, infinity), rec)) {
    //   return 0.5 * (rec.normal + color(1,1,1));
    // }

    // vec3 unit_direction = unit_vector(r.direction());
    // auto a = 0.5*(unit_direction.y() + 1.0);
    // return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
  }
};

#endif