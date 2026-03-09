#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

// linearly blend white and blue
color ray_color(const ray& r) {
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5
                  *(unit_direction.y() + 1.0);

  return (1.0-a)*color(1.0,1.0,1.0) 
          + (a)*color(0.5,0.7,1.0);
}

int main() {
  // Image dimesions
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // calculate hight, at least 1
  // Simplifies to 9*(16 parts) or H*(W/16) ... flip right side...
  int image_height = image_width/(aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;


  // Camera

  auto focal_length = 1.0;
  auto viewport_height = 2.0;

  // Multiplying the viewport height by the aspect ratio ensures that the 
  // viewport maintains the same proportions as the image.
  auto viewport_width = viewport_height *  (double(image_width)/image_height);
  auto camera_center = point3(0,0,0);

  // vectors across the horizontal and down the verical viewport edges.
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  //  horizontal and vertical delta vectors from pixel to pixel.
  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  // camera's left corner 
  auto viewport_upper_left = camera_center 
                                    - vec3(0,0,focal_length) // z
                                    - viewport_u/2  // x
                                    - viewport_v/2; // y
  
  // Image's left corner (offset from viewport's)
  auto pixel00_loc = viewport_upper_left 
                      + 0.5 
                      * (pixel_delta_u + pixel_delta_v);

  // Render loop: output PPM file to stdout.
  // PPM header: P3 (ASCII format), width, height, max color value (255).
  std::cout << "P3\n" 
            << image_width 
            << ' ' 
            << image_height 
            << "\n255\n";

  // Scanline through pixels 
  for (int j = 0; j < image_height; j++) {
  
    std::clog << "\rScanlines remaining: " 
              << (image_height - j) 
              << ' '
              << std::flush;

    for (int i = 0; i < image_width; i++) {

      auto pixel_center = pixel00_loc 
                                + (i * pixel_delta_u) 
                                + (j * pixel_delta_v);

      auto ray_direction = pixel_center 
                                  - camera_center;

      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  // Final status message; padding spaces clear any leftover progress text.
  std::clog << "\rDone.                   \n";

  return 0;
}