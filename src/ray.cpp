#include "ray.h"

tuple ray::position(double t)
{
	return origin + (direction*t);
}
