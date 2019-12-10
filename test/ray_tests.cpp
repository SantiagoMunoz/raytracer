#include <gtest/gtest.h>
#include "ray.h"
#include "sphere.h"

TEST(RayTest, Creation)
{
	tuple pos{1.0,2.0,3.0, POINT};
	tuple direction{3.0, 4.0, 1.1, VECTOR};
	
	ray r{pos, direction};

	ASSERT_TRUE(r.origin == pos);
	ASSERT_TRUE(r.direction == direction);
}

TEST(RayTest, Position)
{
	tuple pos{0.0, 1.0, 0.0, POINT};
	tuple direction{2.0, 2.0, -2.0, VECTOR};
	ray r{pos, direction};

	tuple pos2 = r.position(0.5);

	ASSERT_TRUE(is_equal(pos2.x, 1.0));
	ASSERT_TRUE(is_equal(pos2.y, 2.0));
	ASSERT_TRUE(is_equal(pos2.z, -1.0));
}

TEST(RayTest, IntersectionWithSphere)
{
	ray r{tuple{0,0,-5, POINT}, tuple{0,0,1, VECTOR}};
	sphere s{tuple{0, 0, 0, POINT}, 1.0};

	auto i = s.collides(r);

	ASSERT_EQ(i.size(), 2);
	ASSERT_TRUE(is_equal(i[0], 6.0));
	ASSERT_TRUE(is_equal(i[1], 4.0));


}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
