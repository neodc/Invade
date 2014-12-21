#ifndef EFFECT_H
#define EFFECT_H

#include <iostream>

enum class Effect : char{
	NO_EFFECT = 1,
	INCREASED_MOVEMENT = 2,
	INCREMENT_SOLDIER = 3,
	IMPROVED_ATTACK = 4,
	CHANGE_SOLDIER = 5,
	TWO_EFFECT = 6
};

std::ostream & operator<< (std::ostream & out, const Effect& in);


bool operator<(const Effect & first, const Effect & second);
bool operator>(const Effect & first, const Effect & second);
bool operator<=(const Effect & first, const Effect & second);
bool operator>=(const Effect & first, const Effect & second);

bool operator<(const int first, const Effect & second);
bool operator>(const int first, const Effect & second);
bool operator<=(const int first, const Effect & second);
bool operator>=(const int first, const Effect & second);
bool operator==(const int first, const Effect & second);
bool operator!=(const int first, const Effect & second);

bool operator<(const Effect & first, const int second);
bool operator>(const Effect & first, const int second);
bool operator<=(const Effect & first, const int second);
bool operator>=(const Effect & first, const int second);
bool operator==(const Effect & first, const int second);
bool operator!=(const Effect & first, const int second);

#endif // EFFECT_H
