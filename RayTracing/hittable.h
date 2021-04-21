#ifndef HITTABLE_H
#define HITTABLE_H

#include "material.h"
#include "ray.h"

/**
 * @param p ray vector to point of contact
 * @param normal normal
 * @param t ray_param
 * @param front_face check the direction of surface
 * @param set_face_normal find the correct direction of the normal
 */
struct hit_record {
  point3 p;
  vec3 normal;
  shared_ptr<material> mat_ptr;
  double t;
  bool front_face;

  inline void set_face_normal(const ray &r, const vec3 &outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual bool hit(const ray &r, double t_min, double t_max,
                   hit_record &rec) const = 0; // making a pure virtual function
};

#endif
