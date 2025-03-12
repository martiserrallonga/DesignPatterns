#pragma once
#include <ostream>
#include <string>
using namespace std;

class CodeBuilder
{
public:
	// ReSharper disable once CppNonExplicitConvertingConstructor
	CodeBuilder(const std::string& className) // NOLINT(modernize-pass-by-value)
	{
		// todo
	}
	CodeBuilder& addField(const string& name, const string& type) {
		// todo
	}

	friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
	{
		// todo
	}

};
