#ifndef __WORLD_H_
#define __WORLD_H_

#include "light.h"
#include "canvas.h"
#include "ray.h"
#include <vector>

struct world
{
    std::vector<object*> objects;
    std::vector<light> lightsources;

    color castRay(ray r);
    bool isPointInShadow(tuple point, light lightsource);
};

struct camera
{
    camera (int width, int height, double depth, tuple pos, tuple dir) : depth{depth}, pos{pos}, dir{dir} {
        screen = new canvas(width, height);
    }

    ~camera() {
        delete screen;

    }

    canvas *screen;
    double depth;
    tuple pos; //To the top left corner of the "canvas"
    tuple dir;

    void render(world *w);
};


#endif /* __WORLD_H_ */
