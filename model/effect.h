#ifndef EFFECT_H
#define EFFECT_H

#include <iostream>

enum class Effect : char{
	NO_EFFECT,
	INCREASED_MOVEMENT,
	INCREMENT_SOLDIER,
	IMPROVED_ATTACK,
	CHANGE_SOLDIER,
	TWO_EFFECT
};

std::ostream & operator<< (std::ostream & out, const Effect& in);

Effect convert(unsigned effect);
#endif // EFFECT_H
