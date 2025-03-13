#include "Creational/FactoryMethod.h"
#include "Creational/AbstractFactory.h"
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

TEST(Factory, InnerFactory) {
	const float angle = asinf(3.f / 5.f);
	const auto polarPoint = Point::Factory::Polar(5.f, angle);
	const auto cartesianPoint = Point::Factory::Cartesian(4.f, 3.f);
	EXPECT_EQ((std::ostringstream() << polarPoint).str(), (std::ostringstream() << cartesianPoint).str());
}

TEST(Factory, AbstractFactory) {
	DrinkFactory factory;
	const auto drink = factory.make("coffee");

	Coffee coffeeExample;
	EXPECT_EQ(drink->prepare(200), coffeeExample.prepare(200));
}

TEST(Factory, FunctionalFactory) {
	DrinkWithVolumeFactory factory;
	const auto drink = factory.make("coffee");

	Coffee coffeeExample;
	EXPECT_EQ(drink->prepare(50), coffeeExample.prepare(50));
}