#pragma once
#include <map>
#include <sstream>

class HotDrink // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	virtual ~HotDrink() = default;
	virtual std::string prepare(int volume) = 0;
};

class Tea : public HotDrink
{
public:
	std::string prepare(const int volume) override {
		std::ostringstream oss;
		oss << "Take tea bag, boil water, pour " << volume
			<< "ml, add some lemon\n";
		return oss.str();
	}
};

class Coffee : public HotDrink
{
public:
	std::string prepare(const int volume) override {
		std::ostringstream oss;
		oss << "Grind some beans, boil water, pour " << volume
			<< "ml, add cream\n";
		return oss.str();
	}
};

class HotDrinkFactory  // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	virtual ~HotDrinkFactory() = default;
	virtual std::unique_ptr<HotDrink> make() const = 0;
};

class TeaFactory : public HotDrinkFactory
{
public:
	std::unique_ptr<HotDrink> make() const override {
		return std::make_unique<Tea>();
	}
};

class CoffeeFactory : public HotDrinkFactory
{
public:
	std::unique_ptr<HotDrink> make() const override {
		return std::make_unique<Coffee>();
	}
};

class DrinkFactory
{
public:
	DrinkFactory() {
		_factories.try_emplace("tea", std::make_unique<TeaFactory>());
		_factories.try_emplace("coffee", std::make_unique<CoffeeFactory>());
	}

	std::unique_ptr<HotDrink> make(const std::string& type) {
		const auto it = _factories.find(type);
		if (it == _factories.end()) return nullptr;
		return it->second->make();
	}

private:
	std::map<std::string, std::unique_ptr<HotDrinkFactory>> _factories;
};