#ifndef __MATRIX_H_
#define __MATRIX_H_

#include <cmath>
#include "tuple.h"

#ifndef PI
#define PI 3.14159265
#endif

struct matrix {

matrix(int w, int h): width{w}, height{h}
{
	elems = new double*[height];
	for(int i=0; i < height; i++)
		elems[i] = new double[width];
}

matrix(int s): width{s}, height{s}
{
	elems = new double*[height];
	for(int i=0; i < height; i++)
		elems[i] = new double[width];
	/* Make identity matrix */
	for(int j=0; j < height; j++)
		for(int i=0; i < height; i++)
			elems[j][i] = (i == j) ? 1.0 : 0.0;
}

~matrix()
{
	for(int i=0; i< height; i++)
		delete []elems[i];
	delete []elems;
}
	int get_width() const;
	int get_height() const;

	double get(int i, int j) const;
	void set(int i, int j, double value);

	matrix operator*(const matrix& A);
	tuple operator*(const tuple&A);

	matrix get_transpose();
	matrix get_submatrix(int row, int column);
	double det();
	matrix inverse();


private:
	int width;
	int height;
	double** elems;
	double det2x2();
	double minor3x3(int row, int column);
	double cofactor3x3(int row, int column);
};

bool operator==(const matrix& A, const matrix& B);

/* Transformations */
matrix translation(double x, double y, double z);
matrix scaling(double x, double y, double z);
matrix rotate_x(double angle);
matrix rotate_y(double angle);
matrix rotate_z(double angle);
matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

#endif /* __MATRIX_H_ */
