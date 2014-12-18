#include "position.h"

std::ostream & operator<< ( std::ostream & out, const Position& in){
	out << '{' << in.x << ',' << in.y << '}';
	return out;
}
