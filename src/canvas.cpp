#include<fstream>
#include "canvas.h"

inline int dtoppm(double& d)
{
	if (d < 0)
		return 0;
	if (d > 1)
		return 255;
	return d*255;
}
color canvas::get_pixel(int width, int height)
{
	return pixels[width][height];
}

void canvas::set_pixel(int width, int height, color& c)
{
	pixels[width][height] = c;
}

void canvas::save_to_disk(const char* filename)
{
	std::ofstream f;
	f.open(filename);
	f << "P3" << std::endl;
	f << width << " " << height << std::endl;
	f << "255" << std::endl;
	for(int j=0; j < height; j++){
		for(int i = 0; i < width; i++)
			f << dtoppm(pixels[j][i].r) << " " << dtoppm(pixels[j][i].g) << " " << dtoppm(pixels[j][i].b) << " ";
		f << std::endl;
	}
	f.close();
}
