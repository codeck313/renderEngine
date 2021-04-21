#include <iostream>

#include "color_1.h"
#include "constant_project.h"
#include "vec3.h"

int main() {

  // Image

  const int image_width = 1024;
  const int image_height = 1024;

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(double(i) / (image_width - 1), 0.15,
                        double(j) / (image_height - 1));
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
}
