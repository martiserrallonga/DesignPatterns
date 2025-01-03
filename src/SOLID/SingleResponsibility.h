#pragma once

#include <format>
#include <fstream>
#include <string>
#include <vector>

struct Journal {
	std::string title;
	std::vector<std::string> entries;

	explicit Journal(std::string title) : title(std::move(title)) {}

	void addEntry(const std::string& entry) {
		static int count = 1;
		entries.push_back(std::format("{}: {}", count++, entry));
	}

	void save(const std::string& filename) const {
		std::ofstream ofs(filename);
		for (const auto& entry : entries) {
			ofs << entry << '\n';
		}
	}
};

struct PersistenceManager {
	static void save(const Journal& journal, const std::string& filename) {
		std::ofstream ofs(filename);
		for (const auto& entry : journal.entries) {
			ofs << entry << '\n';
		}
	}
};