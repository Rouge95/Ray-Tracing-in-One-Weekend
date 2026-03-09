// A vector has a magnitude (length) and direction.
// A Ray extends infinitely in a particular direction.

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
        ray() {}

        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        // getters
        const point3& origin() const { return orig; }
        const vec3& direction() const { return dir; }

        // for a given magnitude t, find the location of the ray
        point3 at(double t) const {
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;
};

#endif