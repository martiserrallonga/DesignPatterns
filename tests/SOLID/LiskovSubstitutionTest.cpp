#include "LiskovSubstitution.h"
#include <gtest/gtest.h>

TEST(LiskovSubstitution, BreakPrinciple) {
	Rectangle r{ 8, 10 };
	const int rArea = TrimRectangleHeight(r, 5);
	EXPECT_EQ(rArea, r.computeArea());

	Square sq{ 10 };
	const int sqArea = TrimRectangleHeight(sq, 5);
	EXPECT_NE(sqArea, sq.computeArea());
	// Should be equal, but width and height are bounded in the Square shape.
}
