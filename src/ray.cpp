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

void ray::collide_with(std::vector<object*> *objects)
{
	for(std::vector<object*>::iterator it = objects->begin(); it < objects->end(); it++)
		collide_with(*it);

	//if (get_hit() != std::nullopt) {
		//tuple pos = position(get_hit()->t);
		////To avoid acne, move a little hit away from the object
		//pos = pos + get_hit()->obj->get_unary_normal_at(pos).direction * 0.01;
		//ray to_lightsource = lightsource.origin - pos;
		//to_lightsource.collide_with(objects);
		//if (to_lightsource.get_hit() != std::nullopt)
			//get_hit()->inShadow = true;
	//}
}

std::optional<intersection> ray::get_hit()
{
	intersection *current_min = NULL;
	std::vector<intersection>::iterator it;

	if (collisions.size() == 0)
		return std::nullopt;

	for(it = collisions.begin(); it < collisions.end(); it++) {
		if ((*it).t < 0)
			continue;
		if (!current_min)
			current_min = &(*it);
		else if ((*it).t < current_min->t)
			current_min = &(*it);
	}

	if (!current_min)
		return std::nullopt;
	else
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
		if (ref > 0) {
				specular = lightsource.intensity * hit->obj->mat.specular * pow(ref, hit->obj->mat.shinyness);
		}
	}

	return ambient + diffuse + specular;
}
