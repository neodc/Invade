#include "dicetype.h"

std::ostream & operator<< ( std::ostream & out, const DiceType& in){
	switch (in){
	case DiceType::ABS:
		out << "abscissa";
		break;
	case DiceType::ORD:
		out << "ordinate";
		break;
	case DiceType::COM:
		out << "command";
		break;
	case DiceType::EFF:
		out << "effect";
		break;
	case DiceType::ATT:
		out << "attack";
		break;
	}
	return out;
}
