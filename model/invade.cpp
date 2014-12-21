#include "invade.h"

Invade::Invade(): current_{Side::NORTH}, winner_{Side::NORTH}, phase_{Phase::NO_PLAYER}{}

const Board & Invade::board() const{ return board_; }
const Player & Invade::player(const Side side){ return players_.at(side); }
Side Invade::current() const{ return current_; }
Side Invade::winner() const{ return winner_; }
Phase Invade::phase() const{ return phase_; }

void Invade::begin(const std::string p1, const std::string p2){
	players_.clear();
	players_.insert(std::make_pair(Side::NORTH, Player{p1}));
	players_.insert(std::make_pair(Side::SOUTH, Player{p2}));
	current_ = Side::NORTH;
	phase_ = Phase::PLAYING_DICE;
	effects_[1] = Effect::NO_EFFECT;
	effects_[2] = Effect::NO_EFFECT;
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
		nbActions_ = players_.at(current_).dice(DiceType::COM);
	}
}

bool Invade::choseEffect(Effect effect, UnitType elite){
	bool ok = false;
	if (phase_ != Phase::PLAYING_EFFECT){
		return false;
	}
	if (effects_.empty()){
		if (effect <= players_.at(current_).dice(DiceType::EFF)){
			effects_.push_back(effect);
			applyEffect(effect, elite);
			ok = true;
		}
	}else if (effects_.size() == 1){
		if (players_.at(current_).dice(DiceType::EFF) == Effect::TWO_EFFECT
				&& effect >= 2 && effect <= 4
				&& effects_[0] >= 2 && effects_[0] <= 4){
			effects_.push_back(effect);
			applyEffect(effect);
			endEffect();
			ok = true;
		}

	}
	return ok;
}


void Invade::applyEffect(Effect effect, UnitType elite){
	switch (effect) {
		case Effect::NO_EFFECT:
			//NO_EFFECT
			break;
		case Effect::INCREASED_MOVEMENT:
			//IMPROVED_MOVEMENT : checked in the movement method
			break;
		case Effect::INCREMENT_SOLDIER:
			//INCREMENT_SOLDIER
			players_.at(current_).addUnit(UnitType::NORMAL);
			break;
		case Effect::IMPROVED_ATTACK:
			//IMPROVED_ATTACK : checked in the attack method
			break;
		case Effect::CHANGE_SOLDIER:
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
	if (phase_ == Phase::PLAYING_MOVE || nbActions_ == 0){
		return false;
	}

	if (board_.unitAt(origin).side() != current_){
		return false;
	}

	bool ok = false;
	unsigned xMovement = Board::distanceX(origin,dest);
	unsigned yMovement = Board::distanceY(origin,dest);

	//TODO ajouter EFFECT::INCRESED_MOVEMENT

	if (xMovement <= players_.at(current_).dice(DiceType::ABS)
			&& yMovement <= players_.at(current_).dice(DiceType::ORD)){
		ok = board_.moveUnit(origin, dest);
		if (ok){
			board_.unitAt(origin).disable();
			nbActions_--;
		}
	}
	return ok;
}

//TODO ajouter la capacité du commandant

void Invade::endMove(){
	if (phase_ == Phase::PLAYING_MOVE){
		phase_ = next(phase_);
		nbActions_ = players_.at(current_).dice(DiceType::COM);
		//TODO bouversement de bataille
	}
}

bool Invade::attack(const Position origin, const Position dest, bool bombshell){
	if (phase_ != Phase::PLAYING_ATTACK){
		return false;
	}

	if (board_.isCaseEmpty(origin)){
		return false;
	}

	if (board_.unitAt(origin).side() != current_){
		return false;
	}

	if (nbActions_ == 0){
		return false;
	}

	bool ok = false;
	unsigned accuracyCurrent = players_.at(current_).dice(DiceType::ATT) + board_.unitAt(origin).type().accuracy();
	unsigned defenceOpponent = players_.at(opponent()).dice(DiceType::ATT) + board_.unitAt(dest).type().accuracy();

	if ((current_ == Side::NORTH && (origin.y < dest.y))
			|| (current_ == Side::SOUTH && (origin.y > dest.y))){
		accuracyCurrent++;
	}
	if (effects_[0] == Effect::IMPROVED_ATTACK || effects_[1] == Effect::IMPROVED_ATTACK){
		accuracyCurrent++;
	}
	//TODO faire la précision de la bombshell

	if (board_.isPositionValid(origin)&& board_.isPositionValid(dest)
			&& board_.canAttack(origin,dest)
			&& (accuracyCurrent > defenceOpponent)){
				if (bombshell){
					//TODO l'attaque de la bombshell
				}
				nbActions_--;
				if (board_.unitAt(dest).reduceHP(1) == 0){
					board_.removeUnit(dest);
				}
				ok = true;
	}
	return ok;
}


void Invade::endAttack(){
	if (phase_ == Phase::PLAYING_ATTACK){
		players_.at(current_).reduceAttack(players_.at(current_).dice(DiceType::ATT) - nbActions_);
		phase_ = next(phase_);
		current_ = opponent();
		players_.at(current_).rollDice();

		//TODO reset les unitées
		//TODO s'occuper de la victoire
	}
}


Side Invade::opponent() const{
	return (current_ == Side::NORTH)? (Side::SOUTH):(Side::NORTH);
}



