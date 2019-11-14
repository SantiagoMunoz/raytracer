#ifndef __TUPLE_H_
#define __TUPLE_H_

#include <math.h>

enum tuple_type {POINT, VECTOR};

#define EPSILON 0.00001
inline bool is_equal (const double &A, const double &B)
{
	return fabs(A-B) < EPSILON;
}

struct tuple {
	tuple (double x, double y, double z, enum tuple_type type) : x{x},y{y},z{z},type{type} {}

	double x;
	double y;
	double z;
	enum tuple_type type;

	tuple operator+(const tuple& A);
	tuple operator-(const tuple& A);
	tuple operator-();

	tuple operator*(const double& d);
	tuple operator/(const double& d);

	double operator*(const tuple&A);
	tuple cross(const tuple &A);

	double magnitude();
	tuple unary();
};

bool operator==(const tuple& A, const tuple& B);

struct color {
	color ( double r, double g, double b) : r{r}, g{g}, b{b} {}
	color () : r{0}, g{0}, b{0} {}

	double r;
	double g;
	double b;

	color operator+(const color& A);
	color operator-(const color& A);
	color operator*(const double& d);
	color operator*(const color& A);
	color operator/(const double& d);
};

bool operator==(const color& A, const color& B);

#endif /* __TUPLE_H_ */
