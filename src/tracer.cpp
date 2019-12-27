#include "canvas.h"
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "world.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char **argv)
{
	camera cam{WIDTH, HEIGHT, 3000, tuple{0, 0, 0, POINT}, tuple{0, 0, 1, VECTOR}};
	sphere s{tuple{WIDTH/4, HEIGHT/2, 500, POINT}, 100, material{color{1, 0.2, 1}, 0.2, 0.9, 0.9, 200}};
	sphere s2{tuple{3*WIDTH/4, HEIGHT/2, 900, POINT}, 100, material{color{1, 1, 0.2}, 0.2, 0.9, 0.9, 200}};
	plane floor{tuple{0,HEIGHT,0,POINT}, tuple{0,-1,0,VECTOR},0,0,material{color{1, 0.2, 0.2}, 0.2, 0.9, 0.9, 200}};

	world scene(&cam);

	//Single lighsource
	scene.lightsources.push_back(light{color{1, 1, 1}, tuple{0, -HEIGHT, -400, POINT}});
	//Single sphere
	scene.objects.push_back(&floor);
	scene.objects.push_back(&s);
	scene.objects.push_back(&s2);

	scene.render();
	scene.cam->screen->save_to_disk("image.ppm");
}
