#ifndef __RAY_H_
#define __RAY_H_

#include "tuple.h"

struct ray
{
	ray (tuple origin, tuple direction) : origin{origin},direction{direction} {}

	tuple origin;
	tuple direction;

	tuple position(double t);

};


#endif /* __RAY_H_ */
