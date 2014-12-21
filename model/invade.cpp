#include "invade.h"

Invade::Invade(): current_{Side::NORTH}, winner_{Side::NORTH}, phase_{Phase::NO_PLAYER}{}

const Board & Invade::board() const{ return board_; }
const Player & Invade::player(const Side side){ return players_.at(side); }
const Side Invade::current() const{ return current_; }
const Side Invade::winner() const{ return winner_; }
const Phase Invade::phase() const{ return phase_; }

void Invade::begin(const std::string p1, const std::string p2){
	players_.clear();
	players_.insert(std::make_pair(Side::NORTH, Player{p1}));
	players_.insert(std::make_pair(Side::SOUTH, Player{p2}));
	winner_= Side::NORTH;
	current_ = Side::NORTH;
	phase_ = Phase::PLAYING_DICE;
	effect1_ = Effect::NO_EFFECT;
	effect2_ = Effect::NO_EFFECT;
	nbMovement_ = 0;
	players_.at(current_).rollDice();
}

void Invade::swapDice(const DiceType d1, const DiceType d2){
	if (phase_ == Phase::PLAYING_DICE){
		players_.at(current_).swapDice(d1,d2);
	}
}

void Invade::endDice(){
	if (phase_ == Phase::PLAYING_DICE){
		phase_ = next(phase_);
		nbMovement_ = players_.at(current_).dice(DiceType::COM);
	}
}

bool Invade::choseEffect(unsigned effect1){
	return choseEffect(effect1, 1, UnitType::NORMAL);
}

bool Invade::choseEffect(unsigned effect1, unsigned effect2){
	return choseEffect(effect1, effect2, UnitType::NORMAL);
}

bool Invade::choseEffect(unsigned effect1, unsigned effect2, UnitType elite){
	if (effect1 < 5 && effect1 > 1 && effect2 < 5 && effect2 > 1 && players_.at(current_).dice(DiceType::EFF) == 6){
		effect1_ = convert(effect1);
		effect2_ = convert(effect2);
		applyEffect(effect1);
		applyEffect(effect2);
		endEffect();
		return true;
	}
	if (effect1 <= players_.at(current_).dice(DiceType::EFF)){
		effect1_ = convert(effect1);
		effect2_ = Effect::NO_EFFECT;
		if (players_.at(current_).dice(DiceType::EFF) == 5){
			applyEffect(effect1, elite);
		}else{
			applyEffect(effect1);
		}
		endEffect();
		return true;
	}
	return false;
}

void Invade::applyEffect(unsigned effect){
	applyEffect(effect, UnitType::NORMAL );
}

void Invade::applyEffect(unsigned effect, UnitType elite){
	switch (effect) {
		case 1:
			//NO_EFFECT
			break;
		case 2:
			//IMPROVED_MOVEMENT : checked in the movement method
			break;
		case 3:
			//INCREMENT_SOLDIER
			players_.at(current_).addUnit(UnitType::NORMAL);
			break;
		case 4:
			//IMPROVED_ATTACK : checked in the attack method
			break;
		case 5:
			//CHANGE_SOLDIER
			if (elite.elite()){
				players_.at(current_).addUnit(elite);
			}
			break;
		default:
			break;
	}
}

void Invade::endEffect(){
	if (phase_ == Phase::PLAYING_EFFECT){
		phase_ = next(phase_);
	}
}

//TODO Permettre d'ajouter un soldat sur le board
bool Invade::move(const Position origin, const Position dest){
	if (nbMovement_ == 0){
		return false;
	}

	if (board_.unitAt(origin).side() != current_){
		return false;
	}

	bool ok = false;
	unsigned xMovement = abs(origin.x - origin.x);
	unsigned yMovement = abs(origin.y - origin.y);

	//TODO ajouter EFFECT::INCRESED_MOVEMENT

	if (phase_ == Phase::PLAYING_MOVE
			&& (xMovement <= players_.at(current_).dice(DiceType::ABS))
			&& (yMovement <= players_.at(current_).dice(DiceType::ORD))){
		ok = board_.moveUnit(origin, dest);
		if (ok){
			board_.unitAt(origin).disable();
			nbMovement_--;
		}
	}
	return ok;
}

//TODO ajouter la capacité du commandant

void Invade::endMove(){
	if (phase_ == Phase::PLAYING_MOVE){
		phase_ = next(phase_);
		//TODO bouversement de bataille
	}
}

bool Invade::attack(const Position origin, const Position dest, bool bombshell){
	if (board_.unitAt(origin).side() != current_){
		return false;
	}

	if (players_.at(current_).dice(DiceType::ATT) == 0){
		return false;
	}

	bool ok = false;
	unsigned accuracyCurrent = players_.at(current_).dice(DiceType::ATT) + board_.unitAt(origin).type().accuracy();
	unsigned defenceOpponent = players_.at(opponent()).dice(DiceType::ATT) + board_.unitAt(dest).type().accuracy();

	if ((current_ == Side::NORTH && (origin.y < dest.y))
			|| (current_ == Side::SOUTH && (origin.y > dest.y))){
		accuracyCurrent++;
	}
	if (effect1_ == Effect::IMPROVED_ATTACK || effect2_ == Effect::IMPROVED_ATTACK){
		accuracyCurrent++;
	}
	//TODO faire la précision de la bombshell

	if (board_.isPositionValid(origin)&& board_.isPositionValid(dest)
			&& board_.canAttack(origin,dest) && phase_ == Phase::PLAYING_ATTACK
			&& (accuracyCurrent > defenceOpponent)){
				if (bombshell){
					//TODO l'attaque de la bombshell
				}
				players_.at(current_).reduceAttack(1);
				if (board_.unitAt(dest).reduceHP(1) == 0){
					board_.removeUnit(dest);
				}
				ok = true;
	}
	return ok;
}


void Invade::endAttack(){
	if (phase_ == Phase::PLAYING_ATTACK){
		phase_ = next(phase_);
		current_ = opponent();
		players_.at(current_).rollDice();
		//TODO reset les unitées
		//TODO s'occuper de la victoire
	}
}


const Side Invade::opponent() const{
	return (current_ == Side::NORTH)? (Side::SOUTH):(Side::NORTH);
}



