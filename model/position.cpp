#include "position.h"

std::ostream & operator<< ( std::ostream & out, const Position& in){
	out << '{' << in.x << ',' << in.y << '}';
	return out;
}

bool operator<(const Position & first, const Position & second){
	return (first.y < second.y) || (first.y == second.y && first.x < second.x);
}
