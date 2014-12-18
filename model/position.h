#ifndef POSITION_H
#define POSITION_H
#include <iostream>

typedef struct{
	unsigned x;
	unsigned y;
} Position;

std::ostream & operator<< (std::ostream & out, Position in);

#endif // POSITION_H
