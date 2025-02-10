#include "Builder.h"
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
