#ifndef __LIGHT_H_
#define __LIGHT_H_

#include "tuple.h"

struct light
{
	light (color intensity, tuple position) : intensity{intensity}, position{position} {}

	color intensity;
	tuple position;
};

#endif /* __LIGHT_H_ */
