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

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
