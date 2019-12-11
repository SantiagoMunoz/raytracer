#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "tuple.h"
#include "ray.h"
#include <vector>

struct sphere : object
{
	sphere (tuple center, double radius) : center{center}, radius{radius} {}

	tuple center;
	double radius;

	std::vector<double> get_collisions(ray &r) override;
};

#endif /* __SPHERE_H_ */
