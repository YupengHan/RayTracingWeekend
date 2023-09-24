#include "rtweekend.hpp"

#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"

#include <iostream>



int main () {
  // World

  hittable_list world;
  
  // auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
  // auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
  // auto material_right  = make_shared<metal>(color(0.99, 0.99, 0.99));
  // auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
  // auto material_center = make_shared<dielectric>(1.5);
  // auto material_left   = make_shared<dielectric>(1.5);
  // auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
  // auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  // auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  // auto material_left   = make_shared<dielectric>(1.5);
  // auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

  // world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
  // world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
  // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
  // world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   -0.4, material_left));
  // world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
  // world.add(make_shared<sphere>(point3(0,0,-3), 2));
  // world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
  // world.add(make_shared<sphere>(point3(1,0,-1), 0.15));
  // world.add(make_shared<sphere>(point3(-1,-0.1,-1), 0.35));
  // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100))
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left   = make_shared<dielectric>(1.5);
  auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

  world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
  world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_width  = 400;
  cam.samples_per_pixel = 100;
  cam.max_reflection_depth = 50;
  cam.vfov = 20;
  cam.lookfrom = point3(-2,2,1);
  cam.lookat   = point3(0,0,-1);
  cam.vup      = vec3(0,1,0);

  cam.render(world);
}