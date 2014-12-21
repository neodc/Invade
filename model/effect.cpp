#include "effect.h"

std::ostream & operator<< ( std::ostream & out, const Effect& in){
	switch (in){
	case Effect::NO_EFFECT:
		out << "no effect";
		break;
	case Effect::INCREASED_MOVEMENT:
		out << "incresed movement";
		break;
	case Effect::INCREMENT_SOLDIER:
		out << "increment soldier";
		break;
	case Effect::IMPROVED_ATTACK:
		out << "improved attack";
		break;
	case Effect::CHANGE_SOLDIER:
		out << "change soldier";
		break;
	case Effect::TWO_EFFECT:
		out << "two effect";
		break;
	}
	return out;
}

Effect convert(unsigned effect){
	switch (effect){
	case 1:
		return Effect::NO_EFFECT;
		break;
	case 2:
		return Effect::INCREASED_MOVEMENT;
		break;
	case 3:
		return Effect::INCREMENT_SOLDIER;
		break;
	case 4:
		return Effect::IMPROVED_ATTACK;
		break;
	case 5:
		return Effect::CHANGE_SOLDIER;
		break;
	default:
		return Effect::NO_EFFECT;
		break;
	}
}
