#pragma once
#include <cmath>
#include <ostream>


class Point
{
public:
	static Point NewCartesian(float x, float y) {
		return { x, y };
	}

	static Point NewPolar(const float r, const float angle) {
		return { r * cos(angle), r * sin(angle) };
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
		return os << "x: " << obj._x << " y: " << obj._y;
	}

private:
	Point(const float x, const float y) : _x(x), _y(y) {}

	float _x;
	float _y;
};
