#include "rtweekend.hpp"
#include "color.hpp"
// #include "vec3.hpp"
// #include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"

#include <iostream>



int main () {
  // World

  hittable_list world;

  // world.add(make_shared<sphere>(point3(0,0,-3), 2));
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
  // world.add(make_shared<sphere>(point3(1,0,-1), 0.15));
  // world.add(make_shared<sphere>(point3(-1,-0.1,-1), 0.35));
  // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100))
  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_width  = 400;

  cam.render(world);
}