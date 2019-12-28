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
	//TODO More elegant way to state origin as a pos
	origin.type = POINT;
	tuple pixel_pos = origin;
	tuple collision_point = origin;
	bool inShadow;
	for (int j=0; j < screen->height; j++) {
		for (int i=0; i < screen->width; i++) {
			pixel_pos = pos + vertical_stride*j + horizontal_stride*i;
			//TODO More elegant way to state as a pos
			pixel_pos.type = POINT;
			ray r{origin, (pixel_pos - origin).unary()};

			r.collide_with(&(w->objects));
			//Handle shadows
			inShadow = false;
			if (r.get_hit() != std::nullopt) {
				tuple collision_point = r.position(r.get_hit()->t) + r.get_hit()->obj->get_unary_normal_at(collision_point).direction*0.05;
				collision_point.type = POINT;
				ray shadow_ray{collision_point, (w->lightsources[0].position - collision_point).unary()};

				shadow_ray.collide_with(&(w->objects));

				if (shadow_ray.get_hit())
					inShadow = true;
			}
			illumination = r.get_illumination(w->lightsources[0], inShadow);
			screen->set_pixel(j, i, illumination);
		}
	}
}
