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
		//Maintain the lowest valid collision a the front of the vector
		if ( !collisions.empty() && ( collisions[0].t < 0 || ((*it < collisions[0].t) && (*it > 0))))
			collisions.insert(collisions.begin(), intersection{*it, o});
		else
			collisions.push_back(intersection{(*it), o});
}

void ray::collide_with(std::vector<object*> *objects)
{
	for(std::vector<object*>::iterator it = objects->begin(); it < objects->end(); it++)
		collide_with(*it);
}

std::optional<intersection> ray::get_hit()
{
	intersection *current_min = NULL;
	std::vector<intersection>::iterator it;

	if (collisions.empty() || (collisions[0].t < 0))
		return std::nullopt;
	return std::make_optional<intersection>(collisions[0]);
}

ray ray::get_transformed(matrix t)
{
	ray r{t*origin, t*direction};
	return r;
}

ray ray::reflect(tuple &normal)
{
	ray r{origin, direction - normal*2*(direction*normal), allowed_bounces-1};
	return r;
}

tuple ray::get_reflected_direction(tuple &normal)
{
	return direction - normal*2*(direction*normal);
}

color ray::get_illumination(light &lightsource, bool inShadow)
{
	/* First version: Phong's reflection model with no secondary rays. Whatever is hit first determines the result */
	std::optional<intersection> hit = get_hit();

	if ((hit == std::nullopt) || (hit->t < 0))
		return color{0, 0, 0};

	tuple pos = position(hit->t);
	tuple normal_vector = hit->obj->get_unary_normal_at(pos).direction;

	color effective_color = hit->obj->mat.col * lightsource.intensity;
	tuple lightvector = (lightsource.position - pos).unary();
	double ldotn = lightvector*normal_vector;

	color ambient =  effective_color * hit->obj->mat.ambient;
	color diffuse{0, 0, 0};
	color specular{0, 0, 0};

	if(inShadow)
		return ambient;

	if (ldotn > 0) {
		diffuse = effective_color * hit->obj->mat.diffuse * ldotn;
		double ref = -(-lightvector - normal_vector*2*((-lightvector)*normal_vector))*direction;
		if (ref > 0 & (hit->obj->mat.shinyness > 0)) {
				specular = lightsource.intensity * hit->obj->mat.specular * pow(ref, hit->obj->mat.shinyness);
		}
	}

	return ambient + diffuse + specular;
}
