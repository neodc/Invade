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
	case Effect::TWO_EFFECTS:
		out << "two effect";
		break;
	}
	return out;
}
//Effect - Effect
bool operator<(const Effect & first, const Effect & second){
	return (static_cast<int>(first) < static_cast<int>(second));
}
bool operator>(const Effect & first, const Effect & second){
	return (static_cast<int>(first) > static_cast<int>(second));
}
bool operator<=(const Effect & first, const Effect & second){
	return (static_cast<int>(first) <= static_cast<int>(second));
}
bool operator>=(const Effect & first, const Effect & second){
	return (static_cast<int>(first) >= static_cast<int>(second));
}
//Int - Effect
bool operator<(const int first, const Effect & second){
	return (first < static_cast<int>(second));
}
bool operator>(const int first, const Effect & second){
	return (first > static_cast<int>(second));
}
bool operator<=(const int first, const Effect & second){
	return (first <= static_cast<int>(second));
}
bool operator>=(const int first, const Effect & second){
	return (first >= static_cast<int>(second));
}
bool operator==(const int first, const Effect & second){
	return (first == static_cast<int>(second));
}
bool operator!=(const int first, const Effect & second){
	return (first != static_cast<int>(second));
}
//Effect - Int
bool operator<(const Effect & first, const int second){
	return (static_cast<int>(first) < second);
}
bool operator>(const Effect & first, const int second){
	return (static_cast<int>(first) > second);
}
bool operator<=(const Effect & first, const int second){
	return (static_cast<int>(first) <= second);
}
bool operator>=(const Effect & first, const int second){
	return (static_cast<int>(first) >= second);
}
bool operator==(const Effect & first, const int second){
	return (static_cast<int>(first) == second);
}
bool operator!=(const Effect & first, const int second){
	return (static_cast<int>(first) != second);
}
