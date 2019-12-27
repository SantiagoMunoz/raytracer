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
	//TODO More elegant way to state origin as a pos
	origin.type = POINT;
	tuple pixel_pos = origin;
	bool inShadow;
	for (int j=0; j < cam->screen->height; j++) {
		for (int i=0; i < cam->screen->width; i++) {
			pixel_pos = cam->pos + vertical_stride*j + horizontal_stride*i;
			//TODO More elegant way to state as a pos
			pixel_pos.type = POINT;
			ray r{origin, (pixel_pos - origin).unary()};

			r.collide_with(&objects);

			//Handle shadows
			inShadow = false;
			illumination = r.get_illumination(lightsources[0], inShadow);
			cam->screen->set_pixel(j, i, illumination);
		}
	}
}
