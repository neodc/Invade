/*!
 * \file unit.h
 * \brief Definition of the Unit class
 */
#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <QJsonObject>

#include "unittype.h"
#include "side.h"
/*!
 * \brief The Unit class
 * Represents a invade unit.
 */
class Unit {
		UnitType type_;
		Side side_;
		unsigned hp_;
		bool enable_;
		unsigned bombshell_;
	public:
		/*!
		 * \brief Unit Constructs a unit.
		 * \param type The unit type.
		 * \param side The side where the unit belongs.
		 */
		Unit(UnitType type = UnitType::NORMAL, Side side = Side::NORTH);
		/*!
		 * \brief Enable the unit and set her to maxHP;
		 */
		void reset();
		/*!
		 * \brief Reduce th unit HP.
		 * \param u Value which reduces the HP.
		 */
		unsigned reduceHP(unsigned u);
		/*!
		 * \brief Reduce th unit Bombshell.
		 * \param u Value which reduces the Bombshell.
		 */
		unsigned reduceBombshell(unsigned u);

		/*!
		 * \brief Returns the unit type.
		 * \return The unit type.
		 */
		const UnitType & type() const;
		/*!
		 * \brief Returns the side where the unit belongs.
		 * \return The side where the unit belongs.
		 */
		const Side & side() const;
		/*!
		 * \brief Returns the unit current HP.
		 */
		unsigned hp() const;
		/*!
		 * \brief Returns the unit current Bomshells.
		 */
		unsigned bombshell() const;
		/*!
		 * \brief Tells if a unit is enabled.
		 * \return True if the unit is enabled, false if not.
		 */
		bool enable() const;
		/*!
		 * \brief Disable the unit.
		 */
		void disable();
		/*!
		 * \brief Update the state of the object to reflect the state of the json object.
		 * \param json The json object to read.
		 */
		void read(const QJsonObject & json);
		/*!
		 * \brief Update the state of the json object to reflect the state of  the object.
		 * \param json The json object to write.
		 */
		void write(QJsonObject & json) const;
};
/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the Unit.
 * \return the output stream.
 */
std::ostream & operator<< (std::ostream & out, const Unit & in);

#endif // UNIT_H
