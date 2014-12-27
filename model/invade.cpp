#include "invade.h"
#include <algorithm>
#include <QJsonArray>

Invade::Invade(): current_{Side::NORTH}, winner_{Side::NORTH}, phase_{Phase::NO_PLAYER}{}

const Board & Invade::board() const{ return board_; }
const Player & Invade::constPlayer(const Side side) const{ return players_.at(side); }
Player & Invade::player(const Side side){ return players_.at(side); }
Side Invade::current() const{ return current_; }
Side Invade::winner() const{ return winner_; }
Phase Invade::phase() const{ return phase_; }

void Invade::reset(){
	effects_.clear();
	board_.clear();
	players_.clear();
	phase_ = Phase::NO_PLAYER;
}

void Invade::begin(const std::string p1, const std::string p2){
	reset();
	players_.insert(std::make_pair(Side::NORTH, Player{p1}));
	players_.insert(std::make_pair(Side::SOUTH, Player{p2}));
	current_ = Side::NORTH;
	phase_ = Phase::PLAYING_DICE;
	player(current_).rollDice();
}

bool Invade::endPhase(){
	switch (phase_){
		case Phase::PLAYING_DICE:
			nbActions_ = player(current_).dice(DiceType::COM);
			break;
		case Phase::PLAYING_EFFECT:
			if( effects_.empty() ){
				return false;
			}
			break;
		case Phase::PLAYING_MOVE:
			player(current_).disruption();
			nbActions_ = player(current_).dice(DiceType::COM);
			break;
		case Phase::PLAYING_COMMANDER:
			break;
		case Phase::PLAYING_ATTACK:
			player(current_).reduceAttack(player(current_).dice(DiceType::ATT) - nbActions_);
			current_ = !current_;
			player(current_).rollDice();
			board_.reset();
			if( isVictory() ){
				phase_ = Phase::END;
				winner_ = current_;
			}

			break;
		default:
			return false;
			break;
	}

	phase_ = next(phase_);
	notifierChangement();
	return true;
}

void Invade::swapDice(const DiceType d1, const DiceType d2){
	if (phase_ == Phase::PLAYING_DICE){
		player(current_).swapDice(d1,d2);
	}
	notifierChangement();
}

bool Invade::chooseEffect(Effect effect, UnitType elite){
	if (phase_ != Phase::PLAYING_EFFECT){
		return false;
	}

	if( hasEffect(effect) ){
		return false;
	}

	bool ok = false;

	if (effects_.empty()){
		if (effect <= player(current_).dice(DiceType::EFF)){
			effects_.insert(effect);
			applyEffect(effect, elite);
			ok = true;
		}
	}else if (effects_.size() == 1){
		Effect e = *(effects_.begin());
		if (player(current_).dice(DiceType::EFF) == Effect::TWO_EFFECTS
				&& effect >= 2 && effect <= 4
				&& e >= 2 && e <= 4){
			effects_.insert(effect);
			applyEffect(effect);
			endPhase();
			ok = true;
		}

	}
	notifierChangement();
	return ok;
}


void Invade::applyEffect(Effect effect, UnitType elite){
	switch (effect) {
		case Effect::NO_EFFECT:
			break;
		case Effect::INCREASED_MOVEMENT:
			//checked in the movement method
			break;
		case Effect::INCREMENT_SOLDIER:
			player(current_).addUnit(UnitType::NORMAL);
			break;
		case Effect::IMPROVED_ATTACK:
			//checked in the attack method
			break;
		case Effect::CHANGE_SOLDIER:
			if (elite.elite()){
				player(current_).addUnit(elite);
			}
			break;
		default:
			break;
	}
}

bool Invade::move(const Position origin, const Position dest){
	if (phase_ != Phase::PLAYING_MOVE || nbActions_ == 0){
		return false;
	}

	if (board_.isCaseEmpty(origin) || board_.unitAt(origin).side() != current_ || !board_.unitAt(origin).enable()){
		return false;
	}

	bool ok = false;
	int diffX = player(current_).dice(DiceType::ABS) - Board::distanceX(origin,dest);
	int diffY = player(current_).dice(DiceType::ORD) - Board::distanceY(origin,dest);

	if( diffX >= 0 && diffY >= 0 ){
		ok = true;
	}else if( hasEffect(Effect::INCREASED_MOVEMENT) && ((diffX >= -1) && (diffY >= -1)) && (diffX >= 0 || diffY >= 0) ){
		ok = true;
	}

	if (ok){
		ok = board_.moveUnit(origin, dest);
		if (ok){
			board_.unitAt(dest).disable();
			nbActions_--;
			if( board_.unitAt(dest).type() == UnitType::ELITE_C ){
				phase_ = Phase::PLAYING_COMMANDER;
				commander_ = dest;
			}
		}
	}
	notifierChangement();
	return ok;
}

bool Invade::addUnit(const Position p, const UnitType type){
	if (phase_ != Phase::PLAYING_MOVE || nbActions_ == 0){
		return false;
	}

	if( !( current_ == Side::NORTH && p.y == 0 ) && !( current_ == Side::SOUTH && p.y == (board_.dimensions().y-1) ) ){
		return false;
	}

	if (!board_.isCaseEmpty(p)){
		return false;
	}

	board_.addUnit(p, Unit{type, current_});
	board_.unitAt(p).disable();
	nbActions_--;
	player(current_).removeUnit(type);
	notifierChangement();

	return true;
}

bool Invade::moveCommander(const Position origin, const Position dest){
	if (phase_ != Phase::PLAYING_COMMANDER){
		return false;
	}

	if (board_.isCaseEmpty(origin) || board_.unitAt(origin).side() != current_){
		return false;
	}

	if( Board::distanceX(origin,dest) != 0 && Board::distanceY(origin,dest) != 0 ){
		return false;
	}

	if( Board::distanceX(origin,commander_) <= Board::distanceX(dest,commander_) || Board::distanceY(origin,commander_) <= Board::distanceY(dest,commander_) ){
		return false;
	}

	if( dest.x != commander_.x && (origin.x < commander_.x) != (dest.x < commander_.x) ){
		return false;
	}

	if( dest.y != commander_.y && (origin.y < commander_.y) != (dest.y < commander_.y) ){
		return false;
	}

	int diff;
	bool ok = false;
	if( Board::distanceX(origin,dest) != 0 ){
		diff = player(current_).dice(DiceType::ABS) - Board::distanceX(origin,dest);
	}else{
		diff = player(current_).dice(DiceType::ORD) - Board::distanceY(origin,dest);
	}

	if( hasEffect(Effect::INCREASED_MOVEMENT) ){
		++diff;
	}

	if ( diff >= 0 ){
		ok = board_.moveUnit(origin, dest);
		if (ok){
			if( board_.unitAt(dest).type() == UnitType::ELITE_C ){
				commander_ = dest;
			}else{
				endPhase();
			}
		}
	}
	return ok;
}

bool Invade::attack(const Position origin, const Position dest, bool bombshell){
	if (phase_ != Phase::PLAYING_ATTACK || nbActions_ == 0){
		return false;
	}

	if (!board_.isPositionValid(origin) || board_.isCaseEmpty(origin) || board_.unitAt(origin).side() != current_){
		return false;
	}

	if (!board_.isPositionValid(dest) || board_.isCaseEmpty(dest) || board_.unitAt(dest).side() == current_){
		return false;
	}

	bool ok = false;
	unsigned accuracyCurrent = player(current_).dice(DiceType::ATT) + board_.unitAt(origin).type().accuracy();
	unsigned defenseOpponentBase = player(!current_).dice(DiceType::ATT);
	unsigned defenseOpponent = defenseOpponentBase + board_.unitAt(dest).type().accuracy();

	if ((current_ == Side::NORTH && (origin.y < dest.y))
			|| (current_ == Side::SOUTH && (origin.y > dest.y))){
		accuracyCurrent++;
	}
	if (hasEffect(Effect::IMPROVED_ATTACK)){
		accuracyCurrent++;
	}


	if ( board_.canAttack(origin,dest)
			&& (accuracyCurrent > defenseOpponent)){
			if (bombshell){
				Position p = dest;

				p.x = dest.x+1;
				if(board_.isPositionValid(p) && !board_.isCaseEmpty(p)
						&& accuracyCurrent > defenseOpponentBase + board_.unitAt(p).type().accuracy() ){
					if (board_.unitAt(p).reduceHP(1) == 0){
						board_.removeUnit(p);
					}
				}

				p.x = dest.x-1;
				if(board_.isPositionValid(p) && !board_.isCaseEmpty(p)
						&& accuracyCurrent > defenseOpponentBase + board_.unitAt(p).type().accuracy() ){
					if (board_.unitAt(p).reduceHP(1) == 0){
						board_.removeUnit(p);
					}
				}

				p.y = dest.y+1;
				if(board_.isPositionValid(p) && !board_.isCaseEmpty(p)
						&& accuracyCurrent > defenseOpponentBase + board_.unitAt(p).type().accuracy() ){
					if (board_.unitAt(p).reduceHP(1) == 0){
						board_.removeUnit(p);
					}
				}

				p.y = dest.y-1;
				if(board_.isPositionValid(p) && !board_.isCaseEmpty(p)
						&& accuracyCurrent > defenseOpponentBase + board_.unitAt(p).type().accuracy() ){
					if (board_.unitAt(p).reduceHP(1) == 0){
						board_.removeUnit(p);
					}
				}

				++accuracyCurrent;
			}
			nbActions_--;
			if (board_.unitAt(dest).reduceHP(1) == 0){
				board_.removeUnit(dest);
			}
			ok = true;
	}
	return ok;
}

bool Invade::hasEffect(Effect e) const{
	return effects_.count(e) != 0;
}

bool Invade::isVictory(){
	if( player(!current_).nbUnit() == 0 ){
		return true;
	}

	Position p{0, 0};
	if( current_ == Side::NORTH ){
		p.y = board_.dimensions().y-1;
	}

	while (board_.isPositionValid(p)) {
		if( !board_.isCaseEmpty(p) && board_.unitAt(p).side() == current_ ){
			return true;
		}

		++p.x;
	}

	return false;
}


void Invade::read(const QJsonObject &json){
	current_ = static_cast<Side>(json["current"].toInt());
	winner_ = static_cast<Side>(json["winner"].toInt());
	phase_ = static_cast<Phase>(json["phase"].toInt());
	nbActions_ = json["nbActions"].toInt();
	commander_ = str2pos(json["commander"].toString());

	board_.read( json["board"].toObject() );

	QJsonArray players = json["players"].toArray();
	players_.clear();

	for (int i = 0; i < players.size(); ++i) {
		QJsonObject playerObject = players[i].toObject();
		players_[ static_cast<Side>(playerObject["type"].toInt()) ].read( playerObject["value"].toObject() );
	}

	QJsonArray effects = json["effects"].toArray();
	effects_.clear();

	for (int i = 0; i < effects.size(); ++i) {
		effects_.insert( static_cast<Effect>(effects[i].toInt()) );
	}
}

void Invade::write(QJsonObject &json) const{
	json["current"] = static_cast<int>(current_);
	json["winner"] = static_cast<int>(winner_);
	json["phase"] = static_cast<int>(phase_);
	json["nbActions"] = static_cast<int>(nbActions_);
	json["commander"] = pos2str(commander_);

	QJsonObject board;
	board_.write(board);
	json["board"] = board;

	QJsonArray players;

	for( const std::pair<const Side, Player>& p : players_ ){
		QJsonObject playerObject;
		QJsonObject pObject;

		playerObject["type"] = static_cast<int>(p.first);

		p.second.write(pObject);
		playerObject["value"] = pObject;

		players.append(playerObject);
	}

	json["players"] = players;

	QJsonArray effects;

	for( const Effect& e : effects_ ){
		effects.append( static_cast<int>(e) );
	}
}
