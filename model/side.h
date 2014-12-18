#ifndef SIDE_H
#define SIDE_H
#include <iostream>

enum class Side : char{
	NORTH,
	SOUTH
};

std::ostream & operator<< (std::ostream & out, const Side& in);

#endif // SIDE_H
