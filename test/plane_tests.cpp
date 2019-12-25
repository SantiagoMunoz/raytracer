#include <gtest/gtest.h>
#include <optional>
#include "ray.h"
#include "plane.h"

TEST(PlaneTest, CollisionPlaneInfiniteXYPerpendicular)
{
    plane p{tuple{0,0,0,POINT},tuple{0,0,1,VECTOR},0,0};
    ray r{tuple{0,0,-1, POINT}, tuple{0,0,1, VECTOR}};

    r.collide_with(&p);

    ASSERT_TRUE(r.get_hit() != std::nullopt);

    tuple point = r.position(r.get_hit()->t);
    ASSERT_TRUE(is_equal(point.x, 0));
    ASSERT_TRUE(is_equal(point.y, 0));
    ASSERT_TRUE(is_equal(point.z, 0));
}

TEST(PlaneTest, CollisionPlaneInfiniteXZPerpendicular)
{
    plane p{tuple{0,0,0,POINT},tuple{0,1,0,VECTOR},0,0};
    ray r{tuple{0,1,0,POINT}, tuple{0,-1,0, VECTOR}};

    r.collide_with(&p);

    ASSERT_TRUE(r.get_hit() != std::nullopt);

    tuple point = r.position(r.get_hit()->t);
    ASSERT_TRUE(is_equal(point.x, 0));
    ASSERT_TRUE(is_equal(point.y, 0));
    ASSERT_TRUE(is_equal(point.z, 0));
}

TEST(PlaneTest, CollisionPlaneInfiniteXYOffset)
{

    plane p{tuple{0,0,0,POINT},tuple{0,0,1,VECTOR},0,0};
    ray r{tuple{1,1,-1, POINT}, tuple{0,0,1, VECTOR}};

    r.collide_with(&p);

    ASSERT_TRUE(r.get_hit() != std::nullopt);

    tuple point = r.position(r.get_hit()->t);
    ASSERT_TRUE(is_equal(point.x, 1));
    ASSERT_TRUE(is_equal(point.y, 1));
    ASSERT_TRUE(is_equal(point.z, 0));
}

TEST(PlaneTest, CollisionPlaneInfiniteXYAngled)
{
    plane p{tuple{0,0,0,POINT},tuple{0,0,1,VECTOR},0,0};
    ray r{tuple{0,1,-1, POINT}, tuple{0,0,1, VECTOR}};

    r.collide_with(&p);

    ASSERT_TRUE(r.get_hit() != std::nullopt);

    tuple point = r.position(r.get_hit()->t);
    ASSERT_TRUE(is_equal(point.x, 0));
    ASSERT_TRUE(is_equal(point.y, 1));
    ASSERT_TRUE(is_equal(point.z, 0));
}

TEST(PlaneTest, CollisionPlaneInfiniteAngled)
{
    plane p{tuple{0,0,0,POINT}, tuple{0,-sqrt(2)/2,-sqrt(2)/2, VECTOR},0,0};
    ray r{tuple{0,-1,-1,POINT}, tuple{0,-sqrt(2)/2,-sqrt(2)/2, VECTOR}};

    r.collide_with(&p);

    ASSERT_TRUE(r.get_hit() != std::nullopt);

    tuple point = r.position(r.get_hit()->t);
    ASSERT_TRUE(is_equal(point.x, 0));
    ASSERT_TRUE(is_equal(point.y, 0));
    ASSERT_TRUE(is_equal(point.z, 0));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
