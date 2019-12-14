#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "tuple.h"

struct material
{
	material (color col, double ambient, double diffuse, double specular, double shinyness) : col(col), ambient(ambient), diffuse(diffuse), specular(specular), shinyness(shinyness) {}

	color col;
	double ambient;
	double diffuse;
	double specular;
	double shinyness;
};

#endif /* __MATERIAL_H_ */
