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
	color il{0, 0, 0};
	sphere s{tuple{WIDTH/2, HEIGHT/2, 100, POINT}, 100, material{color{0.2, 1, 1}, 0.1, 0.9, 0.9, 200}};
	light l{color{1, 1, 1}, tuple{WIDTH/4, HEIGHT/4, -100, POINT}};

	for(int j=0; j< HEIGHT; j++) {
		for(int i=0; i < WIDTH; i++) {
			ray r{tuple{i, j, 0, POINT}, tuple{0,0,1, VECTOR}};
			r.collide_with(&s);
			if(r.get_hit() != std::nullopt) {
				il = r.get_illumination(l);
				c.set_pixel(j, i, il);
			} else {
				c.set_pixel(j, i, no_color);
			}
		}
	}

	c.save_to_disk("image.ppm");


}
