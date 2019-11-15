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

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
