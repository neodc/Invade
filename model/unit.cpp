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

bool Unit::isEnabled(){
	return enable_;
}

const UnitType& Unit::type() const{ return type_; }
const Side& Unit::side() const{ return side_; }
unsigned Unit::hp() const{ return hp_; }
bool Unit::enable() const{ return enable_; }

void Unit::read(const QJsonObject &json){
	type_ = UnitType::fromId(json["type"].toInt());
	side_ = static_cast<Side>(json["side"].toInt());
	hp_ = json["hp"].toInt();
	enable_ = json["enable"].toBool();
}

void Unit::write(QJsonObject &json) const{
	json["type"] = static_cast<int>(type_.id());
	json["side"] = static_cast<int>(side_);
	json["hp"] = static_cast<int>(hp_);
	json["enable"] = enable_;
}

std::ostream & operator<< (std::ostream & out, const Unit& in){

	out << std::boolalpha << '{' << in.type() << ',' << in.side() << ',' << in.hp() << ',' << in.enable() << '}';

	return out;
}
