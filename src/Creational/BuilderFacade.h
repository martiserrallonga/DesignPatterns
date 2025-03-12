#pragma once
#include <ostream>
#include <string>

class Person2
{
	friend class PersonBuilder;
	friend class PersonAddressBuilder;
	friend class PersonJobBuilder;

public:
	static PersonBuilder create();

	friend std::ostream& operator<<(std::ostream& os, const Person2& obj) {
		return os
			<< "address: " << obj._address << ", "
			<< "postCode: " << obj._postCode << ", "
			<< "city: " << obj._city << ", "
			<< "company: " << obj._company << ", "
			<< "position: " << obj._position << ", "
			<< "income: " << obj._income;
	}

private:
	std::string _address;
	std::string _postCode;
	std::string _city;

	std::string _company;
	std::string _position;
	int _income{ 0 };

};

class PersonBuilderBase
{
public:
	explicit PersonBuilderBase(Person2& person);
	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;

	// ReSharper disable once CppNonExplicitConversionOperator
	operator Person2() const { // This can be done by implementing the build() method
		return std::move(_person);
	}

protected:
	Person2& _person;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class PersonAddressBuilder : public PersonBuilderBase
{
	using Self = PersonAddressBuilder;

public:
	explicit PersonAddressBuilder(Person2& person) : PersonBuilderBase(person) {}

	Self& at(std::string address) {
		_person._address = std::move(address);
		return *this;
	}

	Self& withPostCode(std::string postCode) {
		_person._postCode = std::move(postCode);
		return *this;
	}

	Self& in(std::string city) {
		_person._city = std::move(city);
		return *this;
	}
};

class PersonJobBuilder : public PersonBuilderBase
{
	using Self = PersonJobBuilder;

public:
	explicit PersonJobBuilder(Person2& person) : PersonBuilderBase(person) {}

	Self& at(std::string company) {
		_person._company = std::move(company);
		return *this;
	}

	Self& asA(std::string position) {
		_person._position = std::move(position);
		return *this;
	}

	Self& earning(const int income) {
		_person._income = income;
		return *this;
	}
};

class PersonBuilder : public PersonBuilderBase
{
public:
	PersonBuilder();

private:
	Person2 _personObject;
};

