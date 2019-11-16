#include "matrix.h"

double det2x2(const matrix& A)
{
	return (A.get(0,0)*A.get(1,1)) - (A.get(1,0)*A.get(0,1));
}

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

tuple matrix::operator*(const tuple&A)
{
	tuple res { A.x*elems[0][0] + A.y*elems[0][1] + A.z*elems[0][2] + (A.type == VECTOR ? 1.0 : 0.0)*elems[0][3],
		    A.x*elems[1][0] + A.y*elems[1][1] + A.z*elems[1][2] + (A.type == VECTOR ? 1.0 : 0.0)*elems[1][3],
		    A.x*elems[2][0] + A.y*elems[2][1] + A.z*elems[2][2] + (A.type == VECTOR ? 1.0 : 0.0)*elems[2][3],
		    is_equal(A.x*elems[3][0] + A.y*elems[3][1] + A.z*elems[3][2] + (A.type == VECTOR ? 1.0 : 0.0)*elems[3][3], 0.0) ? POINT : VECTOR};
	return res;
}

matrix matrix::get_transpose()
{
	matrix t{height, width};

	for (int i=0; i<width; i++)
		for (int j=0; j<height; j++)
			t.set(j, i, elems[i][j]);

	return t;
}

matrix matrix::get_submatrix(int row, int column)
{
	matrix m{width-1, height-1};

	for (int i=0; i<height; i++){
		if (i == row)
			continue;
		for (int j=0; j<width; j++) {
			if (j == column)
				continue;
			m.set(i > row ? i-1 : i, j > column ? j-1 : j, elems[i][j]);
		}
	}

	return m;
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