#include "unittype.h"

UnitType::UnitType(unsigned pvMax, int speed, int accuracy, bool elite, unsigned bombshell) :
	pvMax_{pvMax}, speed_{speed}, accuracy_{accuracy}, elite_{elite}, bombshell_{bombshell}{}


unsigned UnitType::pvMax() const{ return pvMax_; }
int UnitType::speed() const{ return speed_; }
int UnitType::accuracy() const{ return accuracy_; }
bool UnitType::elite() const{ return elite_; }
unsigned UnitType::bombshell() const{ return bombshell_; }


const UnitType UnitType::NORMAL		= UnitType(2, 0, 0, false,0);
const UnitType UnitType::ELITE_A	= UnitType(2, -1, 1,true, 0);
const UnitType UnitType::ELITE_B	= UnitType(2, 0, 0, true, 1);
const UnitType UnitType::ELITE_C	= UnitType(2, 0, 0, true, 0);
