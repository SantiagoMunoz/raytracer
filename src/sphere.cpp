#include "sphere.h"

std::vector<double> sphere::get_collisions(ray &r)
{
	std::vector<double> ret;
	double a = (r.direction.x)*(r.direction.x) + (r.direction.y)*(r.direction.y) + (r.direction.z)*(r.direction.z);
	double b = 2*r.direction.x*(r.origin.x - center.x) + 2*r.direction.y*(r.origin.y - center.y) +2*r.direction.z*(r.origin.z - center.z);
	double c = (r.origin.x - center.x)*(r.origin.x - center.x) + (r.origin.y - center.y)*(r.origin.y - center.y) +(r.origin.z - center.z)*(r.origin.z - center.z) - (radius*radius);

	if ((b*b - 4*a*c) >= 0) {
		double t1 = (-b + sqrt(b*b-4*a*c))/(2*a);
		double t2 = (-b - sqrt(b*b-4*a*c))/(2*a);
		ret.push_back(t1);
		if (!is_equal(t1, t2))
			ret.push_back(t2);
	}

	return ret;
}

ray sphere::get_unary_normal_at(tuple &point)
{
	tuple direction = point - center;
	ray r{point, direction.unary()};

	return r;
}
