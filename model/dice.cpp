#include "dice.h"

Dice::Dice(){
	roll();
}

void Dice::roll(){
	value_ = rand() % 6 + 1;
}

unsigned Dice::value() const{
	return value_;
}

void Dice::reduce(unsigned u){
	if( u < value_ ){
		value_ -= u;
	}else{
		value_ = 1;
	}
}

std::ostream & operator<< (std::ostream & out, const Dice& in){
	out << in.value();

	return out;
}
