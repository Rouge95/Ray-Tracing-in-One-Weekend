#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
// 3D vector class: unified abstraction for positions, directions, colors, and
// offsets. Uses semantic aliasing (point3, color) for code clarity without
// enforcing type safety.
class vec3 {
public:
  // Array-based storage enables generic component iteration and indexing.
  double e[3];

  // Default constructor: zero vector (origin, black, null direction).
  vec3() : e{0, 0, 0} {}

  // Parameterized constructor: explicit component initilization.
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  // Semantic accessors: named component extraction (const-safe).
  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  // Unary negation: additive inverse (directional reversal, geometric
  // reflection).
  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  // Index operators: read-only and mutable access for generic algorithms.
  vec3 &operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3 &operator*=(double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  // Compound assignment in-place scalar multiplication uniform scaling.
  vec3 &operator/=(double t) { return *this *= 1 / t; }

  // Euclidean norm geometric length of the vector (expensive sqrt).
  double length() const { return std::sqrt(length_squared()); }

  // Squared norm avoids sqrt() for for magnitude comparisons and relative
  // distance calculations.
  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }
};

// Semantic alias: point3 = vec3 provides code clarity without compile-time type
// enforcement.
using point3 = vec3;

// VECTOR UTILITY FUNCTIONS

// Stream output: enables natural syntax (std::cout << v).
inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Vector addition: component-wise summation (commutative, associative).
inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Vector subtraction: differenece between endpoints or reverse direction.
inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], v.e[2] - u.e[2]);
}

// Hadamard product: element-wise multiplication (used for color blending and
// modulation).
inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Scalar multiplication (left style): uniform scaling of all components.
inline vec3 operator*(double t, const vec3 &v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// Scalar multiplication (right style): commutative scaling (delegates to left
// version)
inline vec3 operator*(const vec3 &v, double t) { return t * v; }

// Scalar division: reciprocal multiplication (delegates to operator* for
// efficiency).
inline vec3 operator/(const vec3 &v, double t) { return (1 / t) * v; }

// Dot product (inner product): sum of component-wise products.
// Geometric meaning: |u||v|cos(θ); orthoganality test; projection maginitude.
inline double dot(const vec3 &u, const vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Cross product perpendicular vector with magnitude = parallelogram area.
// Essential for surface normals, coordinate frames, and handedness detection.
// Only defined in 3D; direction determined by right-hand rule.
inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Unit vector (normalization): produces direction-preserving vector with
// magnitude = 1 critical for encoding pure direction, probability
// distributions, and numeriacal stability.
inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

#endif
