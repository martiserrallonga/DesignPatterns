#include "OpenClosed.h"

#include <iostream>
#include <gtest/gtest.h>

TEST(OpenClosed, NotClosedToModification) {
	Product apple("Apple", EColor::Green, ESize::Small);
	Product tree("Tree", EColor::Green, ESize::Large);
	Product house("House", EColor::Blue, ESize::Large);
	std::vector items{ &apple, &tree, &house };

	auto greenThings = ProductFilter::byColor(items, EColor::Green);
	EXPECT_EQ(greenThings.size(), 2);
	EXPECT_EQ(greenThings.at(0)->name, "Apple");
	EXPECT_EQ(greenThings.at(1)->name, "Tree");

	auto largeThings = ProductFilter::bySize(items, ESize::Large);
	EXPECT_EQ(largeThings.size(), 2);
	EXPECT_EQ(largeThings.at(0)->name, "Tree");
	EXPECT_EQ(largeThings.at(1)->name, "House");

	auto greenAndLargeThings = ProductFilter::byColorAndSize(items, EColor::Green, ESize::Large);
	EXPECT_EQ(greenAndLargeThings.size(), 1);
	EXPECT_EQ(greenAndLargeThings.at(0)->name, "Tree");
}

TEST(OpenClosed, UsingBetterFilter) {
	Product apple("Apple", EColor::Green, ESize::Small);
	Product tree("Tree", EColor::Green, ESize::Large);
	Product house("House", EColor::Blue, ESize::Large);
	std::vector items{ &apple, &tree, &house };

	BetterFilter bf;

	ColorSpecification greenSpec(EColor::Green);
	auto greenThings = bf.filter(items, greenSpec);
	EXPECT_EQ(greenThings.size(), 2);
	EXPECT_EQ(greenThings.at(0)->name, "Apple");
	EXPECT_EQ(greenThings.at(1)->name, "Tree");

	SizeSpecification largeSpec(ESize::Large);
	auto largeThings = bf.filter(items, largeSpec);
	EXPECT_EQ(largeThings.size(), 2);
	EXPECT_EQ(largeThings.at(0)->name, "Tree");
	EXPECT_EQ(largeThings.at(1)->name, "House");

	auto greenAndLargeThings = bf.filter(items, greenSpec && largeSpec);
	EXPECT_EQ(greenAndLargeThings.size(), 1);
	EXPECT_EQ(greenAndLargeThings.at(0)->name, "Tree");
}
