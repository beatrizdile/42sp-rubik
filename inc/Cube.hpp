#pragma once

#include <iostream>
#include <vector>

enum Color {
	RED,
	GREEN,
	BLUE,
	WHITE,
	ORANGE,
	YELLOW
};

class Surface {
public:
	std::vector<std::vector<Color> > surface;

	Surface() : surface(3, std::vector<Color>(3, RED)) {}

	Surface(Color color) : surface(3, std::vector<Color>(3, color)) {}

	Surface(Surface const &other) : surface(other.surface) {}

	Surface &operator=(Surface const &other) {
		if (this != &other)
			surface = other.surface;
		return *this;
	}
};

class Cube {
public:
	Surface front;
	Surface back;
	Surface up;
	Surface down;
	Surface left;
	Surface right;

	Cube()
		: front(RED),
		  back(ORANGE),
		  up(WHITE),
		  down(YELLOW),
		  left(GREEN),
		  right(BLUE)
	{}

	Cube(Cube const &other)
		: front(other.front),
		  back(other.back),
		  up(other.up),
		  down(other.down),
		  left(other.left),
		  right(other.right)
	{}

	Cube &operator=(Cube const &other) {
		if (this != &other) {
			front = other.front;
			back = other.back;
			up = other.up;
			down = other.down;
			left = other.left;
			right = other.right;
		}
		return *this;
	}

	~Cube() {}
};
