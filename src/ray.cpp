#include "ray.h"

tuple ray::position(double t)
{
	return origin + (direction*t);
}

void ray::collide_with(object *o)
{
	auto cols = o->get_collisions(*this);
	std::vector<double>::iterator it;

	for(it = cols.begin(); it < cols.end(); it++)
		collisions.push_back(intersection{(*it), o});
}

std::optional<intersection> ray::get_hit()
{
	intersection *current_min;
	std::vector<intersection>::iterator it;

	if (collisions.size() == 0)
		return std::nullopt;

	for(it = collisions.begin(); it < collisions.end(); it++) {
		if (it == collisions.begin()) {
			current_min = &(*it);
		} else {
			if ((*it).t < current_min->t)
				current_min = &(*it);
		}
	}

	return std::make_optional<intersection>(*current_min);

}

ray ray::get_transformed(matrix t)
{
	ray r{t*origin, t*direction};
	return r;
}
