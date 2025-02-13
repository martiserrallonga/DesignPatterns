#include "Builder.h"
#include "BuilderGroovyStyle.h"
#include <gtest/gtest.h>

namespace
{
	std::string GetHtmlExample() {
		std::ostringstream oss;

		const std::vector<std::string> words{ "hello", "world" };
		oss << "<ul>\n";
		for (const auto& word : words) {
			oss << "  <li>\n"
				<< "    " << word << "\n"
				<< "  </li>\n";
		}
		oss << "</ul>\n";

		return oss.str();
	}
}

TEST(Builder, SimpleBuilder) {
	const std::string htmlExample = GetHtmlExample();

	HtmlBuilder builder("ul");
	builder.addChild("li", "hello");
	builder.addChild("li", "world");
	EXPECT_EQ(htmlExample, builder.str());
}

TEST(Builder, FluidBuilders) {
	const std::string htmlExample = GetHtmlExample();

	HtmlBuilder builder2("ul");
	builder2.addChild("li", "hello").addChild("li", "world");
	EXPECT_EQ(htmlExample, builder2.str());

	HtmlBuilder builder3 = HtmlElement::create("ul").addChild("li", "hello").addChild("li", "world");
	EXPECT_EQ(htmlExample, builder3.str());

	HtmlElement element = HtmlElement::create("ul").addChild("li", "hello").addChild("li", "world").build();
	EXPECT_EQ(htmlExample, element.str());
}

TEST(Builder, GroovyStyle) {
	const std::string htmlExample = "<p>\n"
		"<img src=\"http://example.com\"/>\n"
		"</p>\n";

	const Tag groovyTag =
		P{
			Img { "http://example.com"  }
	};

	std::ostringstream oss;
	oss << groovyTag;
	EXPECT_EQ(htmlExample, oss.str());
}
