#pragma once
#include <memory>
#include <string>

class Weapon
{
	friend class SwordedSkeletonFactory;

public:
	Weapon(std::string type, const int damage)
		: _type(std::move(type))
		, _damage(damage)
	{
	}

	explicit Weapon(const std::unique_ptr<Weapon>& other)
		: _type(other->_type)
		, _damage(other->_damage)
	{
	}

	friend bool operator==(const Weapon& lhs, const Weapon& rhs) {
		return lhs._type == rhs._type
			&& lhs._damage == rhs._damage;
	}

private:
	std::string _type;
	int _damage;
};

class Enemy  // NOLINT(cppcoreguidelines-special-member-functions)
{
	friend class SwordedSkeletonFactory;

public:
	Enemy(std::string type, const int health, std::unique_ptr<Weapon> weapon)
		: _type(std::move(type))
		, _health(health)
		, _weapon(std::move(weapon))
	{
	}

	Enemy(const Enemy& other)
		: _type(other._type)
		, _health(other._health)
		, _weapon(std::make_unique<Weapon>(other._weapon))
	{
	}

	friend bool operator==(const Enemy& lhs, const Enemy& rhs) {
		return lhs._type == rhs._type
			&& lhs._health == rhs._health
			&& *lhs._weapon == *rhs._weapon;
	}

	const std::unique_ptr<Weapon>& getWeapon() {
		return _weapon;
	}

	void setWeapon(std::unique_ptr<Weapon> weapon) {
		_weapon = std::move(weapon);
	}

	void setWeapon(const Weapon& weapon) {
		_weapon = std::make_unique<Weapon>(weapon);
	}


private:
	std::string _type;
	int _health;
	std::unique_ptr<Weapon> _weapon;
};

class SwordedSkeletonFactory
{
public:
	static std::unique_ptr<Enemy> create(const int health, const int damage) {
		static Enemy prototype("skeleton", 0, std::make_unique<Weapon>("sword", 0));
		return create(health, damage, prototype);
	}

private:
	static std::unique_ptr<Enemy> create(const int health, const int damage, const Enemy& prototype) {
		auto result = std::make_unique<Enemy>(prototype);
		result->_health = health;
		result->_weapon->_damage = damage;
		return result;
	}
};