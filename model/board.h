#ifndef BOARD_H
#define BOARD_H
#include <map>
#include <iostream>
#include <QJsonObject>
#include "position.h"
#include "unit.h"

/*!
 * \brief The Board class
 */
class Board {

	private:
		std::map<Position, Unit> units_;
		Position dimensions_;

	public:
		/*!
		 * \brief isAligned Tells if two positions are aligned.
		 * \param p1 the first position.
		 * \param p2 the second position.
		 * \return true if aligned, false if not.
		 */
		static bool isAligned(const Position p1, const Position p2);
		/*!
		 * \brief distance Returns the total distance between two positions.
		 * \param p1 the first position.
		 * \param p2 the second position.
		 */
		static unsigned distance(const Position p1, const Position p2);
		/*!
		 * \brief distanceX Returns the horizontal distance between two positions.
		 * \param p1 the first position.
		 * \param p2 the second position.
		 */
		static unsigned distanceX(const Position p1, const Position p2);
		/*!
		 * \brief distanceY Returns the upright distance between two positions.
		 * \param p1 the first position.
		 * \param p2 the second position.
		 */
		static unsigned distanceY(const Position p1, const Position p2);

		/*!
		 * \brief Construct a board the the given dimenstions.
		 */
		Board(const Position dimensions = {16, 16});
		/*!
		 * \brief dimensions returns the board dimensions.
		 * \return the board dimensions.
		 */
		Position dimensions() const;
		/*!
		 * \brief isPositionValid Tells if a position is valid in the board.
		 * \param pos the position to check
		 * \return true if valid, false if not.
		 */
		bool isPositionValid(Position pos) const;
		/*!
		 * \brief moveUnit move a unit in the board if he can.
		 * \param origin the original position of the unit
		 * \param dest the destination of the unit
		 * \return true if the unit was moved, false if not.
		 */
		bool moveUnit(const Position origin, const Position dest);
		/*!
		 * \brief isPathClear Tells if the unit can move.
		 * \param origin the original position of the unit.
		 * \param dest the destination of the unit.
		 * \return true if the unit can move, false if not.
		 */
		bool isPathClear(const Position origin, const Position dest) const;
		/*!
		 * \brief canAttack Tells if the unit can attack.
		 * \param origin the original position of the unit.
		 * \param dest attacked unit.
		 * \return  true if the unit can attack, false if not.
		 */
		bool canAttack(const Position origin, const Position dest) const;
		/*!
		 * \brief unitAt return the unit at the position pos.
		 * \param pos the unit position.
		 * \return the wanted unit, if there was one.
		 */
		Unit & unitAt(const Position pos);
		/*!
		 * \brief unitAt return the unit at the position pos. can't modify the unit.
		 * \param pos the unit position.
		 * \return the wanted unit, if there was one.
		 */
		const Unit & unitAt(const Position pos) const;
		/*!
		 * \brief addUnit Add a unit in the board.
		 * \param pos the unit position.
		 * \param unit the unit to add.
		 */
		void addUnit(const Position pos, Unit unit);
		/*!
		 * \brief removeUnit Remove a unit in the board.
		 * \param pos the unit position.
		 */
		void removeUnit(const Position pos);
		/*!
		 * \brief isCaseEmpty Tells if a case is empty.
		 * \param pos the case to check.
		 * \return true if the case is empty, false if not.
		 */
		bool isCaseEmpty(const Position pos) const;
		/*!
		 * \brief clear clears the board.
		 */
		void clear();
		/*!
		 * \brief reset reset all the unit in the board.
		 */
		void reset();
		void read(const QJsonObject & json);
		void write(QJsonObject & json) const;
		/*!
		 * \brief operator<< overload
		 * \param out the output stream.
		 * \param in the board.
		 * \return the output stream.
		 */
		friend std::ostream & operator<< (std::ostream & out, const Board & in);
	private:
		bool isPathClear(const Position origin, const Position dest, bool checkLast) const;
};

#endif // BOARD_H
