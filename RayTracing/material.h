#ifndef MATERIAL_H
#define MATERIAL_H

#include "constant_project.h"

struct hit_record;

class material {
public:
  virtual bool scatterd(const ray &r_in, const hit_record &rec,
                        color &attenuation, ray &scatterd) const = 0;
};

#endif
