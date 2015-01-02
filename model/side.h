#ifndef SIDE_H
#define SIDE_H
#include <iostream>

enum class Side : char {
	NORTH,
	SOUTH
};

std::ostream & operator<< (std::ostream & out, const Side & in);
Side operator!(Side s);

#endif // SIDE_H
