#include "BuilderFacade.h"

PersonBuilder Person2::create() {
	return {};
}

PersonBuilderBase::PersonBuilderBase(Person2& person) : _person(person) {}

PersonAddressBuilder PersonBuilderBase::lives() const {
	return PersonAddressBuilder(_person);
}

PersonJobBuilder PersonBuilderBase::works() const {
	return PersonJobBuilder(_person);
}

PersonBuilder::PersonBuilder() : PersonBuilderBase(_personObject) {}

