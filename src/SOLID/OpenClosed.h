#pragma once

#include <string>
#include <vector>

// Your code should be Open to extension but Closed to modification

// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidConstOrRefDataMembers

enum class EColor { Red, Green, Blue };
enum class ESize { Small, Medium, Large };

struct Product {
	std::string name;
	EColor color;
	ESize size;
};

struct ProductFilter {
	static std::vector<Product*> byColor(const std::vector<Product*>& items, const EColor color) {
		std::vector<Product*> result;
		for (const auto& item : items) {
			if (item->color == color) result.push_back(item);
		}
		return result;
	}

	static std::vector<Product*> bySize(const std::vector<Product*>& items, const ESize size) {
		std::vector<Product*> result;
		for (const auto& item : items) {
			if (item->size == size) result.push_back(item);
		}
		return result;
	}

	static std::vector<Product*> byColorAndSize(const std::vector<Product*>& items, const EColor color, const ESize size) {
		std::vector<Product*> result;
		for (const auto& item : items) {
			if (item->color == color && item->size == size) result.push_back(item);
		}
		return result;
	}
};

template<typename T>
struct AndSpecification;

template<typename T>
struct Specification {
	virtual ~Specification() = default;
	virtual bool isSatisfied(const T& item) const = 0;
	AndSpecification<T> operator&&(const Specification& other) const {
		return AndSpecification<T>(*this, other);
	}
};

template<typename T>
struct AndSpecification : Specification<T> {
	const Specification<T>& first;
	const Specification<T>& second;

	explicit AndSpecification(const Specification<T>& first, const Specification<T>& second)
		: first(first)
		, second(second)
	{}
	bool isSatisfied(const T& item) const override {
		return first.isSatisfied(item) && second.isSatisfied(item);
	}
};

template<typename T>
struct Filter {
	virtual ~Filter() = default;
	virtual std::vector<T*> filter(const std::vector<T*>& items, const Specification<T>& spec) const = 0;
};

struct BetterFilter : Filter<Product> {
	std::vector<Product*> filter(const std::vector<Product*>& items, const Specification<Product>& spec) const override {
		std::vector<Product*> result;
		for (const auto& item : items) {
			if (spec.isSatisfied(*item)) result.push_back(item);
		}
		return result;
	}
};

struct ColorSpecification : Specification<Product> {
	EColor color;
	explicit ColorSpecification(const EColor color) : color(color) {}
	bool isSatisfied(const Product& item) const override {
		return item.color == color;
	}
};

struct SizeSpecification : Specification<Product> {
	ESize size;
	explicit SizeSpecification(const ESize size) : size(size) {}
	bool isSatisfied(const Product& item) const override {
		return item.size == size;
	}
};

