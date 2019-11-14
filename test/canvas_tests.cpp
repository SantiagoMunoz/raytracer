#include "canvas.h"
#include <gtest/gtest.h>

TEST(CanvasTest, DefaultValues)
{
	canvas c{32,32};
	color pixel{0, 0, 0};

	for (int i=0; i<32; i++) {
		for (int j = 0; j <32; j++) {
			ASSERT_TRUE(c.get_pixel(i, j) == pixel);
		}
	}
}

TEST(CanvasTest, GetSet)
{

	canvas c{32,32};
	color pixel{0.2, 0.3, 0.9};

	c.set_pixel(12, 12, pixel);

	ASSERT_TRUE(c.get_pixel(12, 12) == pixel);
}



int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
