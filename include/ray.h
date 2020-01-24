#ifndef __RAY_H_
#define __RAY_H_

#include "tuple.h"
#include "matrix.h"
#include "material.h"
#include "light.h"
#include <vector>
#include <optional>

struct object;

struct intersection
{
	intersection (double t, object *obj) : t{t},obj{obj} {}
	double t;
	object *obj;
};

struct ray
{
	ray (tuple origin, tuple direction, int allowed_bounces = 0) : origin{origin},direction{direction},allowed_bounces{allowed_bounces} {}

	tuple origin;
	tuple direction;
	std::vector<intersection> collisions;
	//Raycasting is recursive until a maximum "bounce" depth
	int allowed_bounces;

	tuple position(double t);

	ray get_transformed(matrix transformation);

	void collide_with(object *o);
	void collide_with(std::vector<object*> *objects);
	std::optional<intersection> get_hit();
	ray reflect(tuple &normal);
	tuple get_reflected_direction(tuple &normal);
	color get_illumination(light &lightsource, bool inShadow);
};

struct object {
	object () : mat{material()} {}

	material mat;

	virtual std::vector<double> get_collisions(ray &r) = 0;
	virtual ray get_unary_normal_at(tuple &point) = 0;
};

#endif /* __RAY_H_ */
