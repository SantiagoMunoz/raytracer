#include "ray.h"
#include <cmath>

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

ray ray::reflect(tuple &normal)
{
	ray r{origin, direction - normal*2*(direction*normal)};
	return r;
}

color ray::get_illumination(light &lightsource)
{
	/* First version: Phong's reflection model with no secondary rays. Whatever is hit first determines the result */
	std::optional<intersection> hit = get_hit();

	if (hit == std::nullopt)
		return color{0, 0, 0};

	tuple pos = position(hit->t);
	tuple normal_vector = hit->obj->get_unary_normal_at(pos).direction;

	color effective_color = hit->obj->mat.col * lightsource.intensity;
	tuple lightvector = (lightsource.position - pos).unary();
	double ldotn = lightvector*normal_vector;

	color ambient =  effective_color * hit->obj->mat.ambient;
	color diffuse{0, 0, 0};
	color specular{0, 0, 0};

	if (ldotn > 0) {
		diffuse = effective_color * hit->obj->mat.diffuse * ldotn;
		double ref = -(-lightvector - normal_vector*2*((-lightvector)*normal_vector))*direction;
		if (ref > 0) {
				specular = lightsource.intensity * hit->obj->mat.specular * pow(ref, hit->obj->mat.shinyness);
		}
	}

	return ambient + diffuse + specular;
}
