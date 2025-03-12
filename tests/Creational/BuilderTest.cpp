#include "Builder.h"
#include "BuilderExercise.h"
#include "BuilderFacade.h"
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

// ReSharper disable StringLiteralTypo
TEST(Builder, BuilderFacade) {
	const std::string personExample =
		"address: Javastraat 42, "
		"postCode: 1094 KM, "
		"city: Amsterdam, "
		"company: Github, "
		"position: Developer, "
		"income: 50000";

	const Person2 person = Person2::create()
		.lives()
		.at("Javastraat 42")
		.withPostCode("1094 KM")
		.in("Amsterdam")
		.works()
		.at("Github")
		.asA("Developer")
		.earning(50e3);

	std::ostringstream oss;
	oss << person;

	EXPECT_EQ(personExample, oss.str());
}

TEST(Builder, BuilderExercise) {
	const std::string codeExample = "class Person\n" // NOLINT(clang-diagnostic-invalid-pp-token)
		"{\n"
		"  string name;\n"
		"  int age;\n"
		"};";

	const auto builder = CodeBuilder{ "Person" }.addField("name", "string").addField("age", "int");

	std::ostringstream oss;
	oss << builder;

	EXPECT_EQ(codeExample, oss.str());
}