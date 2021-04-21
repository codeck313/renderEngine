#include <chrono>
#include <iostream>
// #include <thread>
// #include <functional>

using namespace std::chrono;

#include "camera.h"
#include "color.h"
#include "constant_project.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(const ray &r, const hittable_list &world, int depth,
                double diffusion_factor) {
  hit_record rec;

  if (depth <= 0)
    return color(0, 0, 0);

  if (world.hit(r, 0.001, infinity, rec)) {
    point3 target = rec.p + rec.normal + random_in_unit_sphere();
    return diffusion_factor * (ray_color(ray(rec.p, target - rec.p), world,
                                         depth - 1, diffusion_factor));
  }
  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  // return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(1.0, 0.54, 0.1);
}

int main() {

  // Image
  const auto aspect_ratio = 16.0 / 9.0; // width/height
  const int image_width = 1080;         // 1920;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 10;
  const int max_depth = 100;
  const double albedo = 0.35; // 0.35

  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -7), 1));
  world.add(make_shared<sphere>(point3(0, -101, -1), 100));
  world.add(make_shared<sphere>(point3(0, -1, -7), 1));
  world.add(make_shared<sphere>(point3(-0.75, -0.9, -6), 0.17));

  // Camera
  camera cam;
  // Render
  auto start = high_resolution_clock::now();

  // std::vector<uint8_t> image(image_height * image_width * 3);
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  // #pragma omp parallel for
  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth, albedo);
      }
      // pixel_color /= double(samples_per_pixel);
      // pixel_color = color(sqrt(pixel_color.x()), sqrt(pixel_color.y()),
      //                     sqrt(pixel_color.z()));
      // image[3 * (j * image_width + i) + 0] =
      //     int(256 * clamp(pixel_color.x(), 0.0, 0.999));
      // image[3 * (j * image_width + i) + 1] =
      //     int(256 * clamp(pixel_color.y(), 0.0, 0.999));
      // image[3 * (j * image_width + i) + 2] =
      //     int(256 * clamp(pixel_color.z(), 0.0, 0.999));
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }

  // write_image(image, image_width, image_height);
  auto stop = high_resolution_clock::now();
  auto duration_min = duration_cast<minutes>(stop - start);
  auto duration_sec = duration_cast<seconds>(stop - start);

  std::cerr << "\nDone in " << duration_min.count() << " minutes "
            << duration_sec.count() - duration_min.count() * 60 << " seconds\n";
}
