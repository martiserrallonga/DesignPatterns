#pragma once
#include <sstream>
#include <string>
#include <vector>

class HtmlElement
{
public:
	friend class HtmlBuilder;
	static HtmlBuilder create(std::string root);

	std::string str(const int indentLevel = 0) const {
		std::ostringstream oss;
		const int indent = _indentSize * indentLevel;
		const std::string indentStr(indent, ' ');
		oss << indentStr << "<" << _name << ">\n";

		if (!_text.empty()) {
			oss << indentStr << std::string(_indentSize, ' ') << _text << '\n';
		}
		for (const auto& element : _elements) {
			oss << element.str(indentLevel + 1);
		}

		oss << indentStr << "</" << _name << ">\n";
		return oss.str();
	}

private:
	HtmlElement() = default;

	explicit HtmlElement(std::string name, std::string text = "")
		: _name(std::move(name))
		, _text(std::move(text))
	{
	}

	std::string _name;
	std::string _text;
	std::vector<HtmlElement> _elements;
	int _indentSize = 2;
};

class HtmlBuilder
{
public:
	explicit HtmlBuilder(std::string rootName)
		: _root(std::move(rootName))
	{
	}

	HtmlBuilder& addChild(std::string name, std::string text = "") {
		_root._elements.emplace_back(HtmlElement(std::move(name), std::move(text)));
		return *this;
	}

	HtmlElement build() { return _root; }

	std::string str() const { return _root.str(); } // Can be deleted 

	// ReSharper disable once CppNonExplicitConversionOperator
	operator HtmlElement() const { return _root; } // Is replaced by build()

private:
	HtmlElement _root;
};

inline HtmlBuilder HtmlElement::create(std::string root) {
	return HtmlBuilder(std::move(root));
}
