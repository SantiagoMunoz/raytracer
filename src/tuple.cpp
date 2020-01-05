#include "tuple.h"

bool operator==(const tuple& A, const tuple& B)
{
	return is_equal(A.x, B.x) && is_equal(A.y, B.y) && is_equal(A.z, B.z) && (A.type == B.type);
}

tuple tuple::operator+(const tuple& A)
{
	tuple res{x + A.x, y + A.y, z + A.z, VECTOR};

	if (type == POINT && A.type == VECTOR)
		res.type = POINT;

	return res;
}

tuple tuple::operator-(const tuple& A)
{
	tuple res{x - A.x, y - A.y, z - A.z, VECTOR};

	if ((type == POINT) && (A.type == VECTOR))
		res.type = POINT;

	return res;
}

tuple tuple::operator-()
{
	tuple res{-x, -y, -z, type};
	return res;
}

tuple tuple::operator*(const double& d)
{
	tuple res{x*d, y*d, z*d, type};
	return res;
}

tuple tuple::operator/(const double& d)
{
	tuple res{x/d, y/d, z/d, type};
	return res;

}

double tuple::operator*(const tuple&A)
{
	return x*A.x + y*A.y + z*A.z;
}

tuple tuple::cross(const tuple &A)
{
	tuple res{y*A.z - z*A.y, z*A.x - x*A.z, x*A.y - y*A.x, VECTOR};
	return res;
}

double tuple::magnitude()
{
	return sqrt(x*x + y*y + z*z);
}

tuple tuple::unary()
{
	return *this/this->magnitude();
}


color color::operator+(const color& A)
{
	color ret{r+A.r, g+A.g, b+A.b};
	return ret;
}

color color::operator-(const color& A)
{
	color ret{r-A.r, g-A.g, b-A.b};
	return ret;
}

color color::operator*(const double& d)
{
	color ret{r*d, g*d, b*d};
	return ret;
}

color color::operator*(const color& A)
{
	color ret{r*A.r, g*A.g, b*A.b};
	return ret;
}

color color::operator/(const double& d)
{
	color ret{r/d, g/d, b/d};
	return ret;
}

bool operator==(const color& A, const color& B)
{
	return is_equal(A.r, B.r) && is_equal(A.g, B.g) && is_equal(A.b, B.b);
}
