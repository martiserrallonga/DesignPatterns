#pragma once
#include <format>
#include <string>
#include <vector>

// High level modules should not depend on low level modules.
// Both should depend on abstractions.
// Abstractions should not depend on details.
// Details should depend on abstractions.

// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor

enum class ERelationship {
	Parent,
	Child,
	Sibling,
};

struct Person {
	std::string name;
};

struct Relationships // low level
{
	std::vector<std::tuple<Person, ERelationship, Person>> relations;

	void addParentAndChild(const Person& parent, const Person& child) {
		relations.emplace_back(parent, ERelationship::Parent, child);
		relations.emplace_back(child, ERelationship::Child, parent);
	}
};

struct Research // high level
{
	std::vector<std::string> output;

	Research(Relationships& relationships, const std::string& target) {
		for (auto&& [first, relation, second] : relationships.relations) {
			if (first.name == target && relation == ERelationship::Parent) {
				output.emplace_back(std::format("{} has a child called {}", target, second.name));
			}
		}
	}
};


struct IRelationshipBrowser
{
	virtual std::vector<Person> findAllChildrenOf(const std::string& name) = 0;
};

struct BetterRelationships : IRelationshipBrowser
{
	std::vector<std::tuple<Person, ERelationship, Person>> relations;

	void addParentAndChild(const Person& parent, const Person& child) {
		relations.emplace_back(parent, ERelationship::Parent, child);
		relations.emplace_back(child, ERelationship::Child, parent);
	}

	std::vector<Person> findAllChildrenOf(const std::string& name) override {
		std::vector<Person> result;
		for (auto& [first, relation, second] : relations) {
			if (first.name == name && relation == ERelationship::Parent) {
				result.push_back(second);
			}
		}
		return result;
	}
};

struct BetterResearch
{
	std::vector<std::string> output;

	BetterResearch(IRelationshipBrowser& browser, std::string target) {
		for (auto& [childName] : browser.findAllChildrenOf(target)) {
			output.emplace_back(std::format("{} has a child called {}", target, childName));
		}
	}
};
