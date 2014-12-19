#ifndef BOARD_H
#define BOARD_H
#include <map>
#include "position.h"
#include "unit.h"

class Board {

private:
	std::map<Position, Unit> units_;
	const Position dimensions_;

public:
	static bool isAligned(Position p1, Position p2);
	static unsigned distance(Position p1, Position p2);
	static unsigned distanceX(Position p1, Position p2);
	static unsigned distanceY(Position p1, Position p2);

	Board(const Position dimensions = {16, 16});
	bool isPositionValid(Position pos) const;
	bool moveUnit(Position origin, Position dest);
	bool isPathClear(Position origin, Position dest) const;
	const Unit & unitAt(Position pos) const;
	void addUnit(Position pos, Unit & unit);
	void removeUnit(Position pos);
	void attackUnit(Position attacker, Position target);
	bool isCaseEmpty(Position pos) const;
};

#endif // BOARD_H
