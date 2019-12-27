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

	auto i = s.get_collisions(r);

	ASSERT_EQ(i.size(), 2);
	ASSERT_TRUE(is_equal(i[1], 4.0));
	ASSERT_TRUE(is_equal(i[0], 6.0));

}

TEST(RayTest, GetSphereHit)
{
	ray r{tuple{0,0,-5, POINT}, tuple{0,0,1, VECTOR}};
	sphere s{tuple{0, 0, 0, POINT}, 1.0};

	r.collide_with(&s);

	ASSERT_TRUE(is_equal(r.get_hit()->t, 4.0));

}

TEST(RayTest,TranslateRay)
{
	ray r1{tuple{1,2,3, POINT}, tuple{0,1,0, VECTOR}};
	ray r2 = r1.get_transformed(translation(3,4,5));

	ASSERT_TRUE(r1.direction == r2.direction);
	tuple t{4,6,8,POINT};
	ASSERT_TRUE(r2.origin == t);
}

TEST(RayTest, ScaleRay)
{
	ray r1{tuple{1,2,3, POINT}, tuple{0,1,0, VECTOR}};
	ray r2 = r1.get_transformed(scaling(2,3,4));

	tuple t1{2,6,12,POINT};
	ASSERT_TRUE(t1 == r2.origin);
	tuple t2{0,3,0,VECTOR};
	ASSERT_TRUE(t2 == r2.direction);
}

TEST(RayTest, SphereNormal)
{
	sphere s{tuple{0, 0, 0, POINT}, 1.0};

	tuple p{1, 0, 0, POINT};
	tuple n{1, 0, 0, VECTOR};
	ray r = s.get_unary_normal_at(p);
	ASSERT_TRUE(r.direction == n);
	ASSERT_TRUE(r.origin == p);

	tuple p2{sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, POINT};
	tuple n2{sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, VECTOR};
	ray r2 = s.get_unary_normal_at(p2);
	ASSERT_TRUE(r2.direction == n2);
	ASSERT_TRUE(r2.origin == p2);
}

TEST(RayTest, Reflect)
{
	ray r1{tuple{0, 0, -1, POINT}, tuple{1, -1, 0, VECTOR}};
	tuple n1{0, 1, 0, VECTOR};
	tuple ref1{1, 1, 0, VECTOR};
	ASSERT_TRUE(r1.reflect(n1).direction == ref1);

	ray r2{tuple{0, 0, -1, POINT}, tuple{0, -1, 0, VECTOR}};
	tuple n2{sqrt(2)/2, sqrt(2)/2, 0, VECTOR};
	tuple ref2{1, 0, 0, VECTOR};
	ASSERT_TRUE(r2.reflect(n2).direction == ref2);
}

TEST(RayTest, CalculateColorAtPerpendicular)
{
	ray r{tuple{0,0,-1, POINT}, tuple{0,0,1, VECTOR}};
	sphere s{tuple{0,0,1, POINT}, 1.0};
	light l{color{1,1,1},tuple{0,0,-10, POINT}};

	r.collide_with(&s);

	color result = r.get_illumination(l, false);

	ASSERT_TRUE(is_equal(result.r, 1.9));
	ASSERT_TRUE(is_equal(result.g, 1.9));
	ASSERT_TRUE(is_equal(result.b, 1.9));

}

TEST(RayTest, CalculateColorAt45)
{
	ray r{tuple{0,0,-1, POINT}, tuple{0, -sqrt(2)/2, sqrt(2)/2, VECTOR}};
	sphere s{tuple{0, -sqrt(2)/2, sqrt(2)/2, VECTOR}, 1.0};
	light l{color{1,1,1}, tuple{0, -sqrt(2)/2, -10, POINT}};

	r.collide_with(&s);

	color result = r.get_illumination(l, false);

	ASSERT_TRUE(is_equal(result.r, 1.0));
	ASSERT_TRUE(is_equal(result.g, 1.0));
	ASSERT_TRUE(is_equal(result.b, 1.0));
}

TEST(RayTest, CalculateColorAtPerpendicularLightAt45)
{
	ray r{tuple{0,0,-1, POINT}, tuple{0,0,1, VECTOR}};
	sphere s{tuple{0,0,1, POINT}, 1.0};
	light l{color{1,1,1},tuple{0,10,-10, POINT}};

	r.collide_with(&s);

	color result = r.get_illumination(l, false);

	ASSERT_TRUE(is_equal(result.r, 0.7364));
	ASSERT_TRUE(is_equal(result.g, 0.7364));
	ASSERT_TRUE(is_equal(result.b, 0.7364));
}

TEST(RayTest, CalculateColorAt45LightatOpposite45)
{
	ray r{tuple{0,-1,-1, POINT}, tuple{0, sqrt(2)/2, sqrt(2)/2, VECTOR}};
	sphere s{tuple{0,0,1, POINT}, 1.0};
	light l{color{1,1,1},tuple{0,10,-10, POINT}};

	r.collide_with(&s);

	color result = r.get_illumination(l, false);

	ASSERT_TRUE(is_equal(result.r, 1.6364));
	ASSERT_TRUE(is_equal(result.g, 1.6364));
	ASSERT_TRUE(is_equal(result.b, 1.6364));
}

TEST(RayTest, CalculateColorAtPerpendicularLightBehind)
{
	ray r{tuple{0,0,-1, POINT}, tuple{0,0,1, VECTOR}};
	sphere s{tuple{0,0,1, POINT}, 1.0};
	light l{color{1,1,1},tuple{0,0,10, POINT}};

	r.collide_with(&s);

	color result = r.get_illumination(l, false);

	ASSERT_TRUE(is_equal(result.r, 0.1));
	ASSERT_TRUE(is_equal(result.g, 0.1));
	ASSERT_TRUE(is_equal(result.b, 0.1));

}

TEST(RayTest, RotateRayX)
{
	ray r{tuple{0,0,0, POINT}, tuple{0,0,1,VECTOR}};

	ray r2 = r.get_transformed(rotate_x(PI/4));

	ASSERT_TRUE(is_equal(r2.direction.x, 0));
	ASSERT_TRUE(is_equal(r2.direction.y, -sqrt(2)/2));
	ASSERT_TRUE(is_equal(r2.direction.z, sqrt(2)/2));
}

TEST(RayTest, RotateRayY)
{
	ray r{tuple{0,0,0, POINT}, tuple{0,0,1,VECTOR}};

	ray r2 = r.get_transformed(rotate_y(PI/4));

	ASSERT_TRUE(is_equal(r2.direction.x, sqrt(2)/2));
	ASSERT_TRUE(is_equal(r2.direction.y, 0));
	ASSERT_TRUE(is_equal(r2.direction.z, sqrt(2)/2));
}

TEST(RayTest, RotateRayZ)
{
	ray r{tuple{0,0,0, POINT}, tuple{1,0,0,VECTOR}};

	ray r2 = r.get_transformed(rotate_z(PI/4));

	ASSERT_TRUE(is_equal(r2.direction.x, sqrt(2)/2));
	ASSERT_TRUE(is_equal(r2.direction.y, sqrt(2)/2));
	ASSERT_TRUE(is_equal(r2.direction.z, 0));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
