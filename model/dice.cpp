#include "dice.h"

Dice::Dice(){
	srand (time(NULL));
	roll();
}

void Dice::roll(){
	value = rand() % 6 + 1;
}

unsigned Dice::getValue(){
	return value;
}
