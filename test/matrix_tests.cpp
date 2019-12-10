#include "matrix.h"
#include "tuple.h"
#include <gtest/gtest.h>

TEST(MatrixTest, Identity)
{
	matrix m{4};

	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			ASSERT_TRUE(is_equal(m.get(i,j), (i==j) ? 1.0 : 0.0));
}

TEST(MatrixTest, MultiplyByIdentity)
{
	matrix m{4};
	matrix id{4};

	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			m.set(i, j, i*j);

	matrix p = m*id;

	ASSERT_TRUE(p == m);
}

TEST(MatrixTest, TransposeIdentity)
{
	matrix i1{4};

	matrix i2 = i1.get_transpose();

	ASSERT_TRUE(i1 == i2);
}

TEST(MatrixTest, TransposeGeneric)
{
	matrix m1{4};

	m1.set(2,3, 5.0);
	matrix m2 = m1.get_transpose();

	ASSERT_TRUE(m1.get(2,3) == m2.get(3,2));
}

TEST(MatrixTest, MultiplyIdbyTuple)
{
	tuple t{1 , 2, 3, VECTOR};
	matrix id{4};
	tuple t2 = id*t;

	ASSERT_TRUE(t == t2);
}

TEST(MatrixTest, SubMatrix)
{
	matrix m{4};
	m.set(2, 3, 5.0);
	matrix s = m.get_submatrix(2, 3);
	matrix r{3};
	r.set(2,2, 0.0);
	
	ASSERT_TRUE(s == r);

}

TEST(MatrixTest, Determinant)
{
	matrix m{4};
	m.set(0,0, -2.0);
	m.set(0,1, -8.0);
	m.set(0,2, 3.0);
	m.set(0,3, 5.0);
	m.set(1,0, -3.0);
	m.set(1,1, 1.0);
	m.set(1,2, 7.0);
	m.set(1,3, 3.0);
	m.set(2,0, 1.0);
	m.set(2,1, 2.0);
	m.set(2,2, -9.0);
	m.set(2,3, 6.0);
	m.set(3,0, -6.0);
	m.set(3,1, 7.0);
	m.set(3,2, 7.0);
	m.set(3,3, -9.0);

	ASSERT_EQ(m.det(), -4071);
}

TEST(MatrixTest, Inverse)
{
	matrix m{4};
	m.set(0,0, -5.0);
	m.set(0,1, 2.0);
	m.set(0,2, 6.0);
	m.set(0,3, -8.0);
	m.set(1,0, 1.0);
	m.set(1,1, -5.0);
	m.set(1,2, 1.0);
	m.set(1,3, 8.0);
	m.set(2,0, 7.0);
	m.set(2,1, 7.0);
	m.set(2,2, -6.0);
	m.set(2,3, -7.0);
	m.set(3,0, 1.0);
	m.set(3,1, -3.0);
	m.set(3,2, 7.0);
	m.set(3,3, 4.0);

	ASSERT_TRUE(is_equal(m.det(), 532));

	matrix inv = m.inverse();

	ASSERT_TRUE(is_equal(inv.get(0,0),0.21805));
	ASSERT_TRUE(is_equal(inv.get(0,1),0.45113));
	ASSERT_TRUE(is_equal(inv.get(0,2),0.24060));
	ASSERT_TRUE(is_equal(inv.get(0,3),-0.04511));
	ASSERT_TRUE(is_equal(inv.get(1,0),-0.80827));
	ASSERT_TRUE(is_equal(inv.get(1,1),-1.45677));
	ASSERT_TRUE(is_equal(inv.get(1,2),-0.44361));
	ASSERT_TRUE(is_equal(inv.get(1,3),0.52068));
	ASSERT_TRUE(is_equal(inv.get(2,0),-0.07895));
	ASSERT_TRUE(is_equal(inv.get(2,1),-0.22368));
	ASSERT_TRUE(is_equal(inv.get(2,2),-0.05263));
	ASSERT_TRUE(is_equal(inv.get(2,3),0.19737));
	ASSERT_TRUE(is_equal(inv.get(3,0),-0.52256));
	ASSERT_TRUE(is_equal(inv.get(3,1),-0.81391));
	ASSERT_TRUE(is_equal(inv.get(3,2),-0.30075));
	ASSERT_TRUE(is_equal(inv.get(3,3),0.30639));

}

TEST(MatrixTest, MultiplyByInverse)
{
	matrix A{4};
	matrix B{4};

	A.set(0,0, 3);
	A.set(0,1, -9);
	A.set(0,2, 7);
	A.set(0,3, 3);
	A.set(1,0, 3);
	A.set(1,1, -8);
	A.set(1,2, 3);
	A.set(1,3, -9);
	A.set(2,0, -4);
	A.set(2,1, 4);
	A.set(2,2, 4);
	A.set(2,3, 1);
	A.set(3,0, -6);
	A.set(3,1, 5);
	A.set(3,2, -1);
	A.set(3,3, 1);

	B.set(0,0, 8);
	B.set(0,1, 2);
	B.set(0,2, 2);
	B.set(0,3, 2);
	B.set(1,0, 3);
	B.set(1,1, -1);
	B.set(1,2, 7);
	B.set(1,3, 0);
	B.set(2,0, 7);
	B.set(2,1, 0);
	B.set(2,2, 5);
	B.set(2,3, 4);
	B.set(3,0, 6);
	B.set(3,1, -2);
	B.set(3,2, 0);
	B.set(3,3, 5);

	matrix C = A * B;

	ASSERT_TRUE( (C*B.inverse()) == A);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
