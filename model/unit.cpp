#include "unit.h"

Unit::Unit(UnitType type, Side side):
	type_{type}, side_{side}{

	reset();
}

void Unit::reset(){
	enable_ = true;
	hp_ = type_.hpMax();
}

unsigned Unit::reduceHP(unsigned u){
	if( u > hp_ ){
		hp_ = 0;
	}else{
		hp_ -= u;
	}

	return hp_;
}

void Unit::disable(){
	enable_ = false;
}

const UnitType& Unit::type() const{ return type_; }
const Side& Unit::side() const{ return side_; }
unsigned Unit::hp() const{ return hp_; }
bool Unit::enable() const{ return enable_; }

std::ostream & operator<< (std::ostream & out, const Unit& in){

	out << std::boolalpha << '{' << in.type() << ',' << in.side() << ',' << in.hp() << ',' << in.enable() << '}';

	return out;
}
