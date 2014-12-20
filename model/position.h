#ifndef POSITION_H
#define POSITION_H
#include <iostream>

typedef struct{
	unsigned x;
	unsigned y;
} Position;

std::ostream & operator<< (std::ostream & out, const Position& in);

bool operator<(const Position & first, const Position & second);

bool operator==(const Position & first, const Position & second);
bool operator!=(const Position & first, const Position & second);

#endif // POSITION_H
