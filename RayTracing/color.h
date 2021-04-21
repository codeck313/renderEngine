#ifndef COLOR_H
#define COLOR_H

#include "constant_project.h"
#include "vec3.h"
#include <iostream>
#include <vector>

void write_color(std::ostream &out, color pixel_color, int sample_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  auto scale = 1.0 / sample_per_pixel;
  r = (scale * r);
  g = (scale * g);
  b = (scale * b);
  out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void write_image(std::vector<uint8_t> &image, int image_width,
                 int image_height) {
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int j = image_height - 1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      std::cout << static_cast<int>(image[3 * (j * image_width + i) + 0])
                << " ";
      std::cout << static_cast<int>(image[3 * (j * image_width + i) + 1])
                << " ";
      std::cout << static_cast<int>(image[3 * (j * image_width + i) + 2])
                << std::endl;
    }
  }
}

#endif
