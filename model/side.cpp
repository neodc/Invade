#include "side.h"

std::ostream & operator<< ( std::ostream & out, const Side& in){
	switch (in){
	case Side::NORTH:
		out << "north";
		break;
	case Side::SOUTH:
		out << "south";
		break;
	}
	return out;
}
