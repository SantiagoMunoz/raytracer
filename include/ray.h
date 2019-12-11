#ifndef __RAY_H_
#define __RAY_H_

#include "tuple.h"
#include <vector>

struct intersection;

struct ray
{
	ray (tuple origin, tuple direction) : origin{origin},direction{direction} {}

	tuple origin;
	tuple direction;
	std::vector<intersection> collisions;
	
	tuple position(double t);

};

struct object {
	virtual std::vector<double> get_collisions(ray &r) = 0;
};

struct intersection
{
	intersection (double t, object *obj) : t{t},obj{obj}  {}
	double t;
	object *obj;

};

#endif /* __RAY_H_ */
