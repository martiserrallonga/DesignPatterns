#include "Creational/Prototype.h"
#include <gtest/gtest.h>

TEST(Prototype, SimplePrototype) {
	const Enemy skeleton("skeleton", 100, std::make_unique<Weapon>("sword", 5));
	Enemy zombie{ skeleton };
	EXPECT_EQ(skeleton, zombie);

	zombie.setWeapon({ "axe", 7 });
	EXPECT_NE(skeleton, zombie);
}

TEST(Prototype, PrototypeFactory) {
	const auto enemyEasy = SwordedSkeletonFactory::create(100, 5);
	const auto enemyHard = SwordedSkeletonFactory::create(100, 15);
	EXPECT_NE(*enemyEasy, *enemyHard);

	enemyHard->setWeapon({ "sword", 5 });
	EXPECT_EQ(*enemyEasy, *enemyHard);
}