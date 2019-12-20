#include "canvas.h"
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "sphere.h"
#include "world.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char **argv)
{
  camera cam{WIDTH, HEIGHT, 3000, tuple{0, 0, 0, POINT}, tuple{0, 0, 1, VECTOR}};
	sphere s{tuple{WIDTH/2, HEIGHT/2, 300, POINT}, 100, material{color{1, 0.2, 1}, 0.2, 0.9, 0.9, 200}};
	world scene(&cam);

	//Single lighsource
	scene.lightsources.push_back(light{color{1, 1, 1}, tuple{WIDTH/4, HEIGHT/4, -200, POINT}});
	//Single sphere
	scene.objects.push_back(&s);

	scene.render();
	scene.cam->screen->save_to_disk("image.ppm");
}
