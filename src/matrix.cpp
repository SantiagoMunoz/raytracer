#include "matrix.h"
#include "tuple.h"

int matrix::get_width() const
{
	return width;
}

int matrix::get_height() const
{
	return height;
}

double matrix::get(int i, int j) const
{
	return elems[i][j];
}

void matrix::set(int i, int j, double value)
{
	elems[i][j] = value;
}

matrix matrix::operator*(const matrix& A)
{
	matrix res{A.width, height};
	double tmp;
	for(int i=0; i<height; i++) {
		for(int j=0; j < A.width; j++) {
			tmp = 0.0;
			for(int k=0; k < width ; k++) {
				tmp += elems[i][k] * A.get(k, j);
			}
			res.set(i,j, tmp);
		}
	}
	return res;
}

matrix matrix::get_transpose()
{
	matrix t{height, width};

	return t;
}

bool operator==(const matrix& A, const matrix& B) {
	if ((A.get_width() != B.get_width()) || A.get_height() != B.get_height())
		return false;

	for(int j=0; j < B.get_height(); j++)
		for(int i = 0; i < B.get_width(); i++)
			if (!is_equal(A.get(i,j),B.get(i,j)))
				return false;

	return true;
}
