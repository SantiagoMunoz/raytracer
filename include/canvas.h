#ifndef __CANVAS_H_
#define __CANVAS_H_

#include <iostream>

#include "tuple.h"

struct canvas {

	canvas (int width, int height) : width{width},height{height}
	{
		pixels = new color*[height];
		for(int i=0; i<height; i++) {
			pixels[i] = new color[width];
		}
	}

	~canvas()
	{
		for(int i=0; i<height; i++) {
			delete []pixels[i];
		}
		delete []pixels;
	}

	color get_pixel(int width, int height);
	void set_pixel(int width, int height, color c);
	void save_to_disk(const char* filename);

	int width;
	int height;
private:
	color** pixels;
};


#endif /* __CANVAS_H_ */
