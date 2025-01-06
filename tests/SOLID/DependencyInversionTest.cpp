#include "DependencyInversion.h"
#include <gtest/gtest.h>

TEST(DependencyInversion, BreakPrinciple) {
	const Person parent{ "John" };
	const Person child1{ "Chris" };
	const Person child2{ "Matt" };

	Relationships relationships;
	relationships.addParentAndChild(parent, child1);
	relationships.addParentAndChild(parent, child2);

	const Research research{ relationships, parent.name};
	EXPECT_EQ(research.output.at(0), "John has a child called Chris");
	EXPECT_EQ(research.output.at(1), "John has a child called Matt");
}

TEST(DependencyInversion, ApplyPrinciple) {
	const Person parent{ "John" };
	const Person child1{ "Chris" };
	const Person child2{ "Matt" };

	BetterRelationships relationships;
	relationships.addParentAndChild(parent, child1);
	relationships.addParentAndChild(parent, child2);

	const BetterResearch research{ relationships, parent.name};
	EXPECT_EQ(research.output.at(0), "John has a child called Chris");
	EXPECT_EQ(research.output.at(1), "John has a child called Matt");
}
