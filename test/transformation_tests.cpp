#include "matrix.h"
#include "tuple.h"
#include <gtest/gtest.h>

TEST(TransformationTest, Translation)
{
	matrix t = translation(5, -3, 2);
	matrix t2 = t.inverse();
	tuple p{-3, 4, 5, POINT};

	tuple p2 = t*p;
	tuple m{2, 1, 7, POINT};
	ASSERT_TRUE(p2 == m);

	tuple p3 = t2*p;
	tuple m2{-8, 7, 3, POINT};
	ASSERT_TRUE(p3 == m2);
}

TEST(TransformationTest, Scaling)
{
	matrix s = scaling(2, 3, 4);

	tuple p{-4, 6, 8, POINT};
	tuple p2{-8, 18, 32, POINT};
	ASSERT_TRUE(s*p == p2);

	tuple v{-4, 6, 8, VECTOR};
	tuple v2{-8, 18, 32, VECTOR};
	ASSERT_TRUE(s*v == v2);
}

TEST(TransformationTest, RotX)
{
	matrix r = rotate_x(PI/4);

	tuple p{0,1,0, POINT};
	tuple p2{0,sqrt(2)/2, sqrt(2)/2, POINT};
	ASSERT_TRUE(r*p == p2);
}

TEST(TransformationTest, RotY)
{
	matrix r = rotate_y(PI/4);

	tuple p{0,0,1, POINT};
	tuple p2{sqrt(2)/2, 0, sqrt(2)/2, POINT};
	ASSERT_TRUE(r*p == p2);
}

TEST(TransformationTest, RotZ)
{
	matrix r = rotate_z(PI/4);

	tuple p{0, 1, 0, POINT};
	tuple p2{-sqrt(2)/2, sqrt(2)/2, 0, POINT};
	ASSERT_TRUE(r*p == p2);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
