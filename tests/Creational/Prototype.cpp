#include "Creational/Prototype.h"
#include <gtest/gtest.h>


TEST(Prototype, SimplePrototype) {
	const Enemy skeleton("skeleton", 100, std::make_unique<Weapon>("sword", 5));
	Enemy zombie{ skeleton };
	EXPECT_EQ(skeleton, zombie);

	zombie.setWeapon({ "axe", 7 });
	EXPECT_NE(skeleton, zombie);
}