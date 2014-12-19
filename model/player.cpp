#include "player.h"

Player::Player(std::string name) : name_{name}{

	dice_[DiceType::ABS];
	dice_[DiceType::ATT];
	dice_[DiceType::COM];
	dice_[DiceType::EFF];
	dice_[DiceType::ORD];

	units_[UnitType::NORMAL] = 17;
	units_[UnitType::ELITE_A] = 1;
	units_[UnitType::ELITE_B] = 1;
	units_[UnitType::ELITE_C] = 1;
}

unsigned Player::dice( const DiceType& type ) const{
	return dice_.at(type).value();
}

void Player::swapDice(const DiceType& t1, const DiceType& t2){
	Dice s = dice_[t1];
	dice_[t1] = dice_[t2];
	dice_[t2] = s;
}

void Player::swapDice(const DiceType& t1, const DiceType& t2, const DiceType& t3){
	swapDice(t1, t2);
	swapDice(t1, t3);
}

void Player::rollDice(){
	for( std::pair<const DiceType, Dice>& d : dice_ ){
		d.second.roll();
	}
}

void Player::reduceAttack(unsigned u){
	dice_[DiceType::ATT].reduce(u);
}

unsigned Player::unit(const UnitType& type) const{
	return units_.at(type);
}

bool Player::addUnit(const UnitType& type){
	if( type.elite() ){
		if( units_[UnitType::NORMAL] > 0 && units_[type] < 3 ){
			--units_[UnitType::NORMAL];
			++units_[type];
			return true;
		}
	}else{
		if( nbUnit() < 20 ){
			++units_[UnitType::NORMAL];
			return true;
		}
	}
	return false;
}

const std::string& Player::name() const{
	return name_;
}

unsigned Player::nbUnit() const{
	unsigned ret = 0;

	for( const std::pair<const UnitType, unsigned>& u : units_ ){
		ret += u.second;
	}

	return ret;
}

std::ostream & operator<< (std::ostream & out, const Player& in){
	out << "{\n\tname: " << in.name_ << "\n\tdice:\n";

	for( const std::pair<const DiceType, Dice>& d : in.dice_ ){
		out << "\t\t" << d.first << " =>\t" << d.second << '\n';
	}

	out << "\tunits:\n";

	for( const std::pair<const UnitType, unsigned>& u : in.units_ ){
		out << "\t\t" << u.first << " =>\t" << u.second << '\n';
	}

	out << '}';

	return out;
}
