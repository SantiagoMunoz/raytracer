#include "matrix.h"

double matrix::det2x2()
{
	return (elems[0][0]*elems[1][1]) - (elems[1][0]*elems[0][1]);
}

double matrix::minor3x3(int row, int column)
{
	return get_submatrix(row, column).det2x2();
}

double matrix::cofactor3x3(int row, int column)
{
	return ((row+column) % 2 ? 1 : -1)*minor3x3(row, column);
}

double matrix::det()
{
	if (width == 2)
		return det2x2();
	double d = 0.0;
	for(int i=0; i<width; i++)
		d += elems[0][i]*get_submatrix(0,i).det()*(i % 2 ? 1 : -1);
	return d;
}

matrix matrix::inverse()
{
	double d = det();
	matrix inverse{width, width};

	for (int j=0; j < height; j++) {
		for (int i=0; i < width; i++) {
			inverse.set(i, j, (get_submatrix(j, i).det() * ((i+j) % 2 ? 1 : -1))/d);
		}
	}

	return inverse;
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
	tuple res { A.x*elems[0][0] + A.y*elems[0][1] + A.z*elems[0][2] + (A.type == POINT ? 1.0 : 0.0)*elems[0][3],
		    A.x*elems[1][0] + A.y*elems[1][1] + A.z*elems[1][2] + (A.type == POINT ? 1.0 : 0.0)*elems[1][3],
		    A.x*elems[2][0] + A.y*elems[2][1] + A.z*elems[2][2] + (A.type == POINT ? 1.0 : 0.0)*elems[2][3],
		    is_equal(A.x*elems[3][0] + A.y*elems[3][1] + A.z*elems[3][2] + (A.type == POINT ? 1.0 : 0.0)*elems[3][3], 0.0) ? VECTOR : POINT};
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

bool operator==(const matrix& A, const matrix& B)
{
	if ((A.get_width() != B.get_width()) || A.get_height() != B.get_height())
		return false;

	for(int j=0; j < B.get_height(); j++)
		for(int i = 0; i < B.get_width(); i++)
			if (!is_equal(A.get(i,j),B.get(i,j)))
				return false;

	return true;
}

matrix translation(double x, double y, double z)
{
	matrix t{4};

	t.set(0, 3, x);
	t.set(1, 3, y);
	t.set(2, 3, z);

	return t;
}

matrix scaling(double x, double y, double z)
{
	matrix t{4};

	t.set(0,0, x);
	t.set(1,1, y);
	t.set(2,2, z);
	
	return t;
}

matrix rotate_x(double angle)
{
	matrix r{4};

	r.set(1,1, cos(angle));
	r.set(1,2, -sin(angle));
	r.set(2,1, sin(angle));
	r.set(2,2, cos(angle));

	return r;
}

matrix rotate_y(double angle)
{
	matrix r{4};

	r.set(0, 0, cos(angle));
	r.set(0, 2, sin(angle));
	r.set(2, 0, -sin(angle));
	r.set(2, 2, cos(angle));

	return r;
}

matrix rotate_z(double angle)
{
	matrix r{4};

	r.set(0, 0, cos(angle));
	r.set(0, 1, -sin(angle));
	r.set(1, 0, sin(angle));
	r.set(1, 1, cos(angle));

	return r;
}

matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
{
	matrix r{4};

	r.set(0, 1, x_y);
	r.set(0, 2, x_z);
	r.set(1, 0, y_x);
	r.set(1, 2, y_z);
	r.set(2, 0, z_x);
	r.set(2, 1, z_y);

	return r;
}
