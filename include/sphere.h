#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "tuple.h"
#include "ray.h"
#include <vector>

struct sphere
{

	sphere (tuple center, double radius) : center{center}, radius{radius} {}
	tuple center;
	double radius;

	std::vector<double> collides(ray &r);
	
};

#endif /* __SPHERE_H_ */
