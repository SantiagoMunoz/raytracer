#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "tuple.h"

struct material
{
	material () : col{color(1,1,1)}, ambient{0.1}, diffuse{0.9}, specular{0.9}, shinyness{200.0}, reflectiveness{0} {}
	material (color col, double ambient, double diffuse, double specular, double shinyness, double reflectiveness = -1) : col(col), ambient(ambient), diffuse(diffuse), specular(specular), shinyness(shinyness), reflectiveness{reflectiveness} {}

	color col;
	double ambient;
	double diffuse;
	double specular;
	double shinyness;
	double reflectiveness;
};

#endif /* __MATERIAL_H_ */
