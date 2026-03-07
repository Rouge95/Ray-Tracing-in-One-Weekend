#include "color.h"
#include "vec3.h"

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
      // Normalized device coordinates: map pizel indices to 0to1 range.
      auto pixel_color = color(
          double(j) / (image_height - 1), // j/H produces vertical gradient.
          double(i) / (image_width - 1),  // i/W produces horixontal gradient.
          0);

      // Quantize and output converts 0to1 color to 0to255 bytes in PPM.
      write_color(std::cout, pixel_color);
    }
  }

  // Final status message; padding spaces clear any leftover progress text.
  std::clog << "\rDone.                   \n";

  return 0;
}