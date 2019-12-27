#ifndef __PLANE_H_
#define __PLANE_H_

#include "tuple.h"
#include "ray.h"
#include "matrix.h"
#include <vector>
#include <optional>

struct plane : object
{
    plane (tuple trcorner, tuple normal, double width, double height) : trcorner(trcorner), normal(normal), width(width), height(height) {}
    plane (tuple trcorner, tuple normal, double width, double height, material m) : trcorner(trcorner), normal(normal), width(width), height(height) {
        mat = m;
    }

    tuple trcorner;
    tuple normal;
    double width;
    double height;

	std::vector<double> get_collisions(ray &r) override;
	ray get_unary_normal_at(tuple &point) override;
};

#endif // __PLANE_H_
