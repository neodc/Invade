#ifndef BOARD_H
#define BOARD_H
#include <map>
#include <iostream>
#include <QJsonObject>
#include "position.h"
#include "unit.h"

class Board {

private:
	std::map<Position, Unit> units_;
	Position dimensions_;

public:
	static bool isAligned(const Position p1, const Position p2);
	static unsigned distance(const Position p1, const Position p2);
	static unsigned distanceX(const Position p1, const Position p2);
	static unsigned distanceY(const Position p1, const Position p2);

	Board(const Position dimensions = {16, 16});
	Position dimensions() const;
	bool isPositionValid(Position pos) const;
	bool moveUnit(const Position origin, const Position dest);
	bool isPathClear(const Position origin, const Position dest) const;
	bool canAttack(const Position origin, const Position dest) const;
	Unit & unitAt(const Position pos);
	const Unit & unitAt(const Position pos) const;
	void addUnit(const Position pos, Unit unit);
	void removeUnit(const Position pos);
	bool isCaseEmpty(const Position pos) const;
	void clear();
	void reset();
	void read(const QJsonObject &json);
	void write(QJsonObject &json) const;
	friend std::ostream & operator<< (std::ostream & out, const Board& in);
private:
	bool isPathClear(const Position origin, const Position dest, bool checkLast) const;
};

#endif // BOARD_H
