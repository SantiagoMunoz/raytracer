#include "canvas.h"
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "sphere.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char **argv)
{

	canvas c{WIDTH, HEIGHT};
	color no_color{0, 0, 0};
	color red{255,0,0};

	sphere s{tuple{WIDTH/2, HEIGHT/2, 100, POINT}, 80};

	for(int j=0; j< HEIGHT; j++) {
		for(int i=0; i < WIDTH; i++) {
			ray r{tuple{i, j, 0, POINT}, tuple{0,0,1, VECTOR}};
			r.collide_with(&s);
			if(r.get_hit() != std::nullopt)
				c.set_pixel(j, i, red);
			else
				c.set_pixel(j, i, no_color);
		}
	}

	c.save_to_disk("image.ppm");


}
