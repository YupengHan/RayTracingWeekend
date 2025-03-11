# write a CMakeLists.txt file build main.cpp
cmake_minimum_required(VERSION 3.10)

project(testRTW) # RayTracingWeekend

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(testRTW main.cpp color.hpp ray.hpp vec3.hpp hittable.hpp sphere.hpp hittable_list.hpp common.hpp)
