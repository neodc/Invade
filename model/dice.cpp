#include "dice.h"

Dice::Dice(){
	srand (time(NULL));
	roll();
}

void Dice::roll(){
	value_ = rand() % 6 + 1;
}

unsigned Dice::value() const{
	return value_;
}

std::ostream & operator<< (std::ostream & out, const Dice& in){
	out << in.value();

	return out;
}
