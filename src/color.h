#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// Semantic alias: color = vec3 for code clarity (RGB matches x, y, z
// components).
using color = vec3;

// Convert floating-point color [0to1],[0to1],[0to1] to 8-bit integer [0,255]
// and output as PPM. uses 255.999 multiplication to defend against
// floating-point rounding errors.
void write_color(std::ostream &out, const color &pixel_color) {
  // Extract RGB components using semantic accessors.
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Quantization: map normalized [0,1] range to byte [0,255].
  // Multiplication by 255.999 provides defensive rounding against
  // floating-point precision loss.
  int rbyte = int(255.999 * r);
  int gbyte = int(255.999 * g);
  int bbyte = int(255.999 * b);

  // PPM format output: space-separated integers, newline per pixel.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif