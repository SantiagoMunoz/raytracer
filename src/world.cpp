#include "world.h"
#include "ray.h"
#include "tuple.h"
#include "matrix.h"

#include <cmath>
#include <iterator>

void camera::render(world* w)
{
	color illumination{0, 0, 0};

	tuple horizontal_stride = rotate_y(PI/2)*dir;
	tuple vertical_stride = rotate_x(-PI/2)*dir;

	tuple origin = (pos + horizontal_stride*(screen->width/2) + vertical_stride*(screen->height/2)) - dir*depth;
	tuple pixel_pos = origin;
	tuple collision_point = origin;
	for (int j=0; j < screen->height; j++) {
		for (int i=0; i < screen->width; i++) {
			pixel_pos = pos + vertical_stride*j + horizontal_stride*i;
			ray r{origin, (pixel_pos - origin).unary(), 1};
			screen->set_pixel(j, i, w->castRay(r));
		}
	}
}

color world::castRay(ray r)
{
	color result{0,0,0};
	bool inShadow = false;

	if(r.allowed_bounces < 0)
		return result;
	r.allowed_bounces--;

	r.collide_with(&objects);
	std::optional<intersection> collision = r.get_hit();

	if (collision != std::nullopt) {
		tuple collision_point = r.position(collision->t);
		collision_point = collision_point + collision->obj->get_unary_normal_at(collision_point).direction*0.05;
		collision_point.type = POINT;

		inShadow = isPointInShadow(collision_point, lightsources[0]);

		result = r.get_illumination(lightsources[0], inShadow);
		//Reflections!
		double ref = collision->obj->mat.reflectiveness;
		if  (ref > 0) {
			tuple collision_normal = collision->obj->get_unary_normal_at(collision_point).direction;
			r.origin= collision_point;
			r.direction = r.reflect(collision_normal).direction;
				result = result*(1 - ref) + castRay(r)*ref;
		}
	}

	return result;
}

bool world::isPointInShadow(tuple point, light lightsource)
{
	ray r(point, (lightsource.position - point).unary());

	r.collide_with(&objects);

	if (r.get_hit() != std::nullopt)
		return true;

	return false;
}
