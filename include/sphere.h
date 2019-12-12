#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "tuple.h"
#include "ray.h"
#include <vector>
#include <optional>

struct sphere : object
{
	sphere (tuple center, double radius) : center{center}, radius{radius} {}

	tuple center;
	double radius;

	std::vector<double> get_collisions(ray &r) override;
	ray get_unary_normal_at(tuple &point) override;

};

#endif /* __SPHERE_H_ */
