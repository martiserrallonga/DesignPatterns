#pragma once

// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions

class Rectangle
{
protected:
	int _width;
	int _height;

public:
	Rectangle(const int width, const int height) : _width(width), _height(height) {}
	virtual ~Rectangle() = default;

	int getWidth() const { return _width; }
	int getHeight() const { return _height; }

	virtual void setWidth(const int width) { _width = width; }
	virtual void setHeight(const int height) { _height = height; }

	int computeArea() const { return _width * _height; }
};

class Square : public Rectangle {
public:
	explicit Square(const int size) : Rectangle(size, size) {}

	void setWidth(const int width) override { _width = _height = width; }
	void setHeight(const int height) override { _width = _height = height; }
};

// If you have a function that takes a base class, you should be able to substitute the base class by any other derived class
inline int TrimRectangleHeight(Rectangle& rectangle, const int maxHeight) {
	if (rectangle.getHeight() <= maxHeight) return rectangle.computeArea();

	const int width = rectangle.getWidth();
	rectangle.setHeight(maxHeight);
	return width * maxHeight;
}
