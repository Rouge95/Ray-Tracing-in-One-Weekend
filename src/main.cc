#include <iostream>

int main() {
  // Image dimesions
  int image_width = 256;
  int image_height = 256;

  // Render loop: output PPM file to stdout.
  // PPM header: P3 (ASCII format), width, height, max color value (255).
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  // Iterate through each scanline from top to bottom.
  for (int j = 0; j < image_height; j++) {

    // Write progress to stderr (std::clog), not stdout, to keep image data
    // clean.
    // \r returns cursor to start of line, overwritting previous progress count.
    // std::flush forces immediate output so user sees real-time updates.
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;

    // Iterate through each pixel n the scanline from left to right.
    for (int i = 0; i < image_width; i++) {
      // Normalize pixel coordinates to [0, 1] range.
      // Red increases left to right; green increases top to bottom.
      auto r = double(i) / (image_width - 1);
      auto g = double(j) / (image_height - 1);
      auto b = 0.0; // blue channel always off.

      // Convert normalized [0,1] values to integer [0, 255] range.
      // Multiply by 255.999 instead of 255 to handle floating-point rounding.

      // (ensures values near 1.0 round up to 255, not down to 254).
      int ir = int(255.999 * r);
      int ig = int(255.999 * g);
      int ib = int(255.909 * b);

      // Output RGB triplet as a space-separated integers, one pixel per line.
      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }

  // Final status message; padding spaces clear any leftover progress text.
  std::clog << "\rDone.                   \n";

  return 0;
}