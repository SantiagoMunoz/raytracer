#include "tuple.h"
#include <gtest/gtest.h>

TEST(TupleTest, PointConstruction)
{
	tuple t{1.1, 2.2, 3.3, POINT};
	ASSERT_EQ(t.type, POINT);
	ASSERT_TRUE(is_equal(1.1, t.x));
	ASSERT_TRUE(is_equal(2.2, t.y));
	ASSERT_TRUE(is_equal(3.3, t.z));
}

TEST(TupleTest, VectorConstruction)
{
	tuple t{1.1, 2.2, 3.3, VECTOR};
	ASSERT_EQ(t.type, VECTOR);
	ASSERT_TRUE(is_equal(1.1, t.x));
	ASSERT_TRUE(is_equal(2.2, t.y));
	ASSERT_TRUE(is_equal(3.3, t.z));
}

TEST(TupleTest, Comparison)
{
	tuple p_a{1.1, 2.3, 4.5, POINT};
	tuple p_b = p_a;

	tuple v_a{1.1, 2.3, 4.5, VECTOR};
	tuple v_b = v_a;

	ASSERT_TRUE(p_a == p_b);
	ASSERT_TRUE(v_a == v_b);
}

TEST(TupleTest, Addition)
{
	tuple a(1.1, 2.2, 3.3, POINT);
	tuple b(1.1, 1.1, 1.1, VECTOR);
	tuple c(1.1, 2.2, 3.3, VECTOR);

	tuple d = a + b;
	ASSERT_TRUE(is_equal(2.2, d.x));
	ASSERT_TRUE(is_equal(3.3, d.y));
	ASSERT_TRUE(is_equal(4.4, d.z));
	ASSERT_EQ(d.type, POINT);

	tuple e = b + c;
	ASSERT_EQ(e.type, VECTOR);
}

TEST(TupleTest, Substraction)
{
	tuple a{1.1, 2.2, 3.3, POINT};
	tuple b{1.0, 1.0, 1.0, POINT};

	tuple c = a - b;

	ASSERT_TRUE(is_equal(0.1, c.x));
	ASSERT_TRUE(is_equal(1.2, c.y));
	ASSERT_TRUE(is_equal(2.3, c.z));
	ASSERT_EQ(c.type, VECTOR);

	tuple d{1.0, 1.0, 1.0, VECTOR};
	tuple e = c - d;
	ASSERT_EQ(e.type, VECTOR);

	tuple f = a - c;
	ASSERT_EQ(f.type, POINT);
}

TEST(TupleTest, Negation)
{
	tuple a{1.1, 2.2, 3.3, VECTOR};
	tuple b = -a;

	ASSERT_TRUE(is_equal(-1.1, b.x));
	ASSERT_TRUE(is_equal(-2.2, b.y));
	ASSERT_TRUE(is_equal(-3.3, b.z));
	ASSERT_EQ(b.type, VECTOR);
}

TEST(TupleTest, ScalarProduct)
{
	tuple a{1.0, 2.0, 3.0, VECTOR};
	tuple b = a * 2;

	ASSERT_TRUE(is_equal(2.0, b.x));
	ASSERT_TRUE(is_equal(4.0, b.y));
	ASSERT_TRUE(is_equal(6.0, b.z));
	ASSERT_EQ(b.type, VECTOR);
}

TEST(TupleTest, ScalarDivision)
{
	tuple a{4.0, 2.0, 1.0, VECTOR};
	tuple b = a / 2.0;

	ASSERT_TRUE(is_equal(2.0, b.x));
	ASSERT_TRUE(is_equal(1.0, b.y));
	ASSERT_TRUE(is_equal(0.5, b.z));
	ASSERT_EQ(b.type, VECTOR);
}

TEST(TupleTest, NormalizationAndMagnitude)
{
	tuple a{1.1, 2.2, 3.3, VECTOR};
	tuple n = a.unary();
	tuple b = n * a.magnitude();

	ASSERT_TRUE(is_equal(n.magnitude(), 1.0));
	ASSERT_TRUE(a == b);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
