#include "world.h"
#include "ray.h"
#include "tuple.h"
#include "matrix.h"

#include <cmath>
#include <iterator>

void world::render()
{
	color illumination{0, 0, 0};

	tuple horizontal_stride = rotate_y(PI/2)*cam->dir;
	tuple vertical_stride = rotate_x(-PI/2)*cam->dir;

	tuple origin = (cam->pos + horizontal_stride*(cam->screen->width/2) + vertical_stride*(cam->screen->height/2)) - cam->dir*cam->depth;
	tuple pixel_pos = origin;
	for (int j=0; j < cam->screen->height; j++) {
		for (int i=0; i < cam->screen->width; i++) {
	        pixel_pos = cam->pos + vertical_stride*j + horizontal_stride*i;
			ray r{origin, (pixel_pos - origin).unary()};

			for(std::vector<object*>::iterator it = objects.begin(); it < objects.end(); it++) {
				r.collide_with(*it);
			}

			illumination = r.get_illumination(lightsources[0]);
			cam->screen->set_pixel(j, i, illumination);
		}
	}
}
