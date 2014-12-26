#include <cmath>
#include "board.h"

bool Board::isAligned(const Position p1, const Position p2){
	return (distanceX(p1, p2) == 0 || distanceY(p1, p2) == 0);
}

unsigned Board::distance(const Position p1, const Position p2){
	return distanceX(p1, p2) + distanceY(p1, p2);
}

unsigned Board::distanceX(const Position p1, const Position p2){
	return abs(p1.x - p2.x);
}

unsigned Board::distanceY(const Position p1, const Position p2){
	return abs(p1.y - p2.y);
}

Board::Board(const Position dimensions) : dimensions_(dimensions){
}

Position Board::dimensions() const{
	return dimensions_;
}

bool Board::isPositionValid(const Position pos) const{
	return (pos.x <= dimensions_.x && pos.y <= dimensions_.y);
}

bool Board::moveUnit(const Position origin, const Position dest){
	if (isPathClear(origin, dest)){
		units_.insert(std::make_pair(dest, units_.at(origin)));
		units_.erase(origin);
		return true;
	}
	return false;
}

bool Board::isPathClear(const Position origin, const Position dest) const{
	return isPathClear(origin, dest, true);
}

bool Board::isPathClear(const Position origin, const Position dest, bool checkLast) const{
	if(!isPositionValid(origin) || !isPositionValid(dest) || (!isCaseEmpty(dest) && checkLast)){
		return false;
	}

	Side side = units_.at(origin).side();
	int xDirection = (origin.x <= dest.x) ? 1 : -1;
	int yDirection = (origin.y <= dest.y) ? 1 : -1;

	for(unsigned u = origin.y + yDirection ; u != dest.y + yDirection ; u += yDirection){
		Position p{origin.x, u};
		if( !isCaseEmpty(p)
				&& !( (units_.at(p).type() == UnitType::ELITE_A) && (units_.at(p).side() == side) )
				&& (checkLast || p != dest) ){
			return false;
		}
	}
	for(unsigned u = origin.x + xDirection ; u != dest.x + xDirection ; u += xDirection){
		Position p{u, dest.y};
		if(!isCaseEmpty(p)
				&& !( (units_.at(p).type() == UnitType::ELITE_A) && (units_.at(p).side() == side) )
				&& (checkLast || p != dest)){
			return false;
		}
	}

	return true;
}

bool Board::canAttack(const Position origin, const Position dest) const{
	return isAligned(origin, dest) && isPathClear(origin, dest, false);
}

Unit &Board::unitAt(const Position pos){
	return units_.at(pos);
}

const Unit &Board::unitAt(const Position pos) const{
	return units_.at(pos);
}

void Board::addUnit(const Position pos, Unit unit){
	if( isPositionValid(pos) ){
		units_.insert(std::make_pair(pos, unit));
	}
}

void Board::removeUnit(const Position pos){
	units_.erase(pos);
}

bool Board::isCaseEmpty(const Position pos) const{
	return (isPositionValid(pos) && units_.count(pos) == 0);
}

void Board::clear(){
	units_.clear();
}

void Board::reset(){
	for( std::pair<const Position, Unit>& u : units_ ){
		u.second.reset();
	}
}

void Board::read(const QJsonObject &json){

	dimensions_ = str2pos( json["dimension"].toString() );

	units_.clear();

	QJsonObject units = json["units"].toObject();
	QJsonObject::ConstIterator i;

	for( i = units.constBegin(); i != units.constEnd(); ++i ){
		QJsonObject o = i.value().toObject();
		Unit u;
		u.read(o);
		units_.insert( std::make_pair( str2pos(i.key()), u) );
	}

}

void Board::write(QJsonObject &json) const{
	json["dimension"] = pos2str(dimensions_);

	QJsonObject units;

	for( const std::pair<const Position, Unit>& u : units_ ){
		QJsonObject o;
		u.second.write(o);
		units[ pos2str(u.first) ] = o;
	}

	json["units"] = units;
}

std::ostream & operator<< (std::ostream & out, const Board& in){

	out << "{\n";

	for( const std::pair<const Position, const Unit>& u : in.units_ ){
		out << "\t" << u.first << " =>\t" << u.second << '\n';
	}

	out << "}";

	return out;
}
