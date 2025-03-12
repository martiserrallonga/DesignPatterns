#include "Creational/FactoryMethod.h"
#include <gtest/gtest.h>


TEST(Factory, FactoryMethod) {
	const float angle = asinf(3.f / 5.f);
	const auto polarPoint = Point::NewPolar(5.f, angle);

	const auto cartesianPoint = Point::NewCartesian(4.f, 3.f);

	EXPECT_EQ((std::ostringstream() << polarPoint).str(), (std::ostringstream() << cartesianPoint).str());
}

TEST(Factory, SimpleFactory) {
	const float angle = asinf(3.f / 5.f);
	const auto polarPoint = PointFactory::Polar(5.f, angle);

	const auto cartesianPoint = PointFactory::Cartesian(4.f, 3.f);

	EXPECT_EQ((std::ostringstream() << polarPoint).str(), (std::ostringstream() << cartesianPoint).str());
}
