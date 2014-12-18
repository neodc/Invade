#include "unit.h"

Unit::Unit(UnitType type, Side side):
	type_{type}, side_{side}{

	reset();
}

void Unit::reset(){
	enable_ = true;
	hp_ = type_.hpMax();
}

unsigned Unit::reductHP(unsigned u){
	if( u > hp_ ){
		hp_ = 0;
	}else{
		hp_ -= u;
	}

	return hp_;
}

const UnitType& Unit::type(){ return type(); }
const Side& Unit::side(){ return side_; }
unsigned Unit::hp(){ return hp_; }
bool Unit::enable(){ return enable_; }
