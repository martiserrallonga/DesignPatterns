#pragma once
#include <ostream>
#include <string>
#include <vector>

using namespace std;

class CodeBuilder
{
public:
	// ReSharper disable once CppNonExplicitConvertingConstructor
	CodeBuilder(const std::string& className) // NOLINT(modernize-pass-by-value)
		: _name(className) {
	}

	CodeBuilder& addField(const string& name, const string& type) {
		_fields.emplace_back(name, type);
		return *this;
	}

	friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
	{
		os << "class " << obj._name << "\n";
		os << "{\n";
		for (const auto& [name, type] : obj._fields)
		{
			os << "  " << type << " " << name << ";\n";
		}
		os << "};";
		return os;
	}

private:
	std::string _name;
	std::vector<std::pair<std::string, std::string>> _fields;
};
