#include "unittype.h"

UnitType::UnitType(unsigned hpMax, int speed, int accuracy, bool elite, unsigned bombshell) :
	id_{nextId_++}, hpMax_{hpMax}, speed_{speed}, accuracy_{accuracy}, elite_{elite}, bombshell_{bombshell}{}


unsigned UnitType::hpMax() const{ return hpMax_; }
int UnitType::speed() const{ return speed_; }
int UnitType::accuracy() const{ return accuracy_; }
bool UnitType::elite() const{ return elite_; }
unsigned UnitType::bombshell() const{ return bombshell_; }
unsigned UnitType::id() const{ return id_; }

bool UnitType::operator==(const UnitType& other) const{
	return id_ == other.id_;
}

bool UnitType::operator!=(const UnitType& other) const{
	return !operator ==(other);
}

bool UnitType::operator<(const UnitType& other) const{
	return id_ < other.id_;
}

std::ostream & operator<< (std::ostream & out, const UnitType& in){

	if( in == UnitType::NORMAL ){
		out << "NORMAL";
	}else if( in == UnitType::ELITE_A ){
		out << "ELITE_A";
	}else if( in == UnitType::ELITE_B ){
		out << "ELITE_B";
	}else if( in == UnitType::ELITE_C ){
		out << "ELITE_C";
	}

	return out;
}

const UnitType & UnitType::fromId(unsigned i){
	if( i == UnitType::ELITE_A.id() ){
		return UnitType::ELITE_A;
	}else if( i == UnitType::ELITE_B.id() ){
		return UnitType::ELITE_B;
	}else if( i == UnitType::ELITE_C.id() ){
		return UnitType::ELITE_C;
	}else{
		return UnitType::NORMAL;
	}
}

unsigned UnitType::nextId_ = 0;

const UnitType UnitType::NORMAL		= UnitType(2, 0, 0, false,0);
const UnitType UnitType::ELITE_A	= UnitType(2, -1, 1,true, 0);
const UnitType UnitType::ELITE_B	= UnitType(2, 0, 0, true, 1);
const UnitType UnitType::ELITE_C	= UnitType(2, 0, 0, true, 0);
