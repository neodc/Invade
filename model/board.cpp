#include <cmath>
#include "board.h"

bool Board::isAligned(Position p1, Position p2){
	return (distanceX(p1, p2) == 0 || distanceY(p1, p2) == 0);
}

unsigned Board::distance(Position p1, Position p2){
	return distanceX(p1, p2) + distanceY(p1, p2);
}

unsigned Board::distanceX(Position p1, Position p2){
	return abs(p1.x - p2.x);
}

unsigned Board::distanceY(Position p1, Position p2){
	return abs(p1.y - p2.y);
}

Board::Board(const Position dimensions) : dimensions_(dimensions){
}

bool Board::isPositionValid(Position pos) const{
	return (pos.x <= dimensions_.x && pos.y <= dimensions_.y);
}

bool Board::moveUnit(Position origin, Position dest){
	if (isPathClear(origin, dest)){
		units_.insert(std::make_pair(dest, units_.at(origin)));
		units_.erase(origin);
		return true;
	}
	return false;
}

bool Board::isPathClear(Position origin, Position dest) const{
	if(!isPositionValid(origin) || !isPositionValid(dest) || !isCaseEmpty(dest)){
		return false;
	}

	Side side = units_.at(origin).side();
	int xDirection = (origin.x <= dest.x) ? 1 : -1;
	int yDirection = (origin.y <= dest.y) ? 1 : -1;

	for(unsigned u = origin.y + yDirection ; u != dest.y + yDirection ; u += yDirection){
		if(!isCaseEmpty({origin.x, u})
				&& (units_.at({origin.x, u}).type() != UnitType::ELITE_A
					|| units_.at({origin.x, u}).side() != side)){
			return false;
		}
	}
	for(unsigned u = origin.x + xDirection ; u != dest.x + xDirection ; u += xDirection){
		if(!isCaseEmpty({u, dest.y})
				&& (units_.at({u, dest.y}).type() != UnitType::ELITE_A
					|| units_.at({u, dest.y}).side() != side)){
			return false;
		}
	}

	return true;
}

const Unit &Board::unitAt(Position pos) const{

}

void Board::addUnit(Position pos, Unit &unit){

}

void Board::removeUnit(Position pos){

}

void Board::attackUnit(Position attacker, Position target){

}

bool Board::isCaseEmpty(Position pos) const{
	return (isPositionValid(pos) && units_.count(pos) == 0);
}
