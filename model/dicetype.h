#ifndef DICETYPE_H
#define DICETYPE_H
#include <iostream>

enum class DiceType : char {
	ABS,
	ORD,
	COM,
	EFF,
	ATT
};

std::ostream & operator<< (std::ostream & out, const DiceType & in);

#endif // DICETYPE_H
