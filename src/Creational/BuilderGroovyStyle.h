#pragma once
#include <sstream>
#include <string>
#include <vector>

class Tag
{
protected:
	Tag(std::string name, std::string text)
		: _name(std::move(name)), _text(std::move(text))
	{
	}

	Tag(std::string name, std::vector<Tag> children)
		: _name(std::move(name)), _children(std::move(children))
	{
	}

	friend std::ostream& operator<< (std::ostream& os, const Tag& tag) {
		os << "<" << tag._name;
		for (const auto& [attributeName, attributeValue] : tag._attributes) {
			os << " " << attributeName << "=\"" << attributeValue << "\"";
		}

		if (tag._children.empty() && tag._text.empty()) {
			os << std::string("/>\n");
			return os;
		}

		os << std::string(">\n");

		if (!tag._text.empty()) {
			os << tag._text << "\n";
		}

		for (const auto& child : tag._children) {
			os << child;
		}

		os << "</" << tag._name << ">\n";
		return os;
	}

	std::string _name;
	std::string _text;
	std::vector<Tag> _children;
	std::vector<std::pair<std::string, std::string>> _attributes;
};

class P : public Tag
{
public:
	explicit P(std::string text) : Tag("p", std::move(text)) {}
	P(const std::initializer_list<Tag>& children) : Tag{ "p", children } {}
};

class Img : public Tag
{
public:
	explicit Img(const std::string& url) : Tag{ "img","" } {
		_attributes.emplace_back("src", url);
	}
};
