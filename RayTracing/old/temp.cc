
// void write_color(color pixel_color, int sample_per_pixel, uint8_t *image,
//                  int nx, int ny) {
//   auto r = pixel_color.x();
//   auto g = pixel_color.y();
//   auto b = pixel_color.z();

//   auto scale = 1.0 / sample_per_pixel;

//   r = sqrt(scale * r);
//   g = sqrt(scale * g);
//   b = sqrt(scale * b);
//   // std::cerr << r << std::flush;
//   image[3 * (j * nx + i) + 0] = 256 * clamp(r, 0.0, 0.999);
//   image[3 * (j * nx + i) + 1] = 256 * clamp(g, 0.0, 0.999);
//   image[3 * (j * nx + i) + 2] = 256 * clamp(b, 0.0, 0.999);
// }

const int k_threads = std::thread::hardware_concurrency();
std::vector<std::thread> threads(k_threads);
for (int t = 0; t < k_threads; ++t) {
  threads[t] = std::thread(std::bind(
      [&](int start, int end, int t) {
        for (int j = start; j < end; j++) {
          for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
              float u = float(i + drand48()) / float(nx);
              float v = float(j + drand48()) / float(ny);
              ray r = cam.get_ray(u, v);
              col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            image[3 * (j * nx + i) + 0] = int(255.99 * col[0]);
            image[3 * (j * nx + i) + 1] = int(255.99 * col[1]);
            image[3 * (j * nx + i) + 2] = int(255.99 * col[2]);
          }
        }
      },
      t * ny / k_threads, (t + 1) == k_threads ? ny : (t + 1) * ny / k_threads,
      t));
}
for (int t = 0; t < k_threads; ++t) {
  threads[t].join();
}
write_image(&image[0], nx, ny);
