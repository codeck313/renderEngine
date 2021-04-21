#ifndef CAMERA_H
#define CAMERA_H

#include "constant_project.h"

class camera {
public:
  camera() {
    const auto aspect_ratio = 16.0 / 9.0; // width/height TODO
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;

    // distance between camera lens and image plane or distance between
    // the projection plane and the projection point
    auto focal_length = 5;

    origin = point3(0, 0, 0);
    horizontal = vec3(viewport_width, 0.0, 0.0);
    vertical = vec3(0.0, viewport_height, 0.0);
    left_lower_corner =
        origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
  }

  ray get_ray(double u, double v) const {
    return ray(origin,
               left_lower_corner + u * horizontal + v * vertical - origin);
  }

private:
  point3 origin;
  point3 left_lower_corner;
  vec3 horizontal;
  vec3 vertical;
};

#endif
