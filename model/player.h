/*!
 * \file player.h
 * \brief Definition of the Player class
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <QJsonObject>

#include "dicetype.h"
#include "dice.h"
#include "unittype.h"
/*!
 * \brief The Player class
 * Represents a invade player.
 */
class Player {
		std::string name_;
		std::map<const DiceType, Dice> dice_;
		std::map<const UnitType, unsigned> units_;
	public:
		/*!
		 * \brief Construct a player.
		 * \param name The player name.
		 */
		Player(std::string name = "");

		/*!
		 * \brief Return the value of the given dice.
		 * \param type The given dice.
		 */
		unsigned dice(const DiceType & type) const;
		/*!
		 * \brief Swaps two dices.
		 * \param t1 The first dice.
		 * \param t2 The second dice.
		 */
		void swapDice(const DiceType & t1, const DiceType & t2);
		/*!
		 * \brief Swaps three dices.
		 * \param t1 The first dice.
		 * \param t2 The second dice.
		 * \param t3 The third dice.
		 */
		void swapDice(const DiceType & t1, const DiceType & t2, const DiceType & t3);
		/*!
		 * \brief Rolls the player dices.
		 */
		void rollDice();
		/*!
		 * \brief Reduce the attack dice.
		 * \param u Value which reduces the dice.
		 */
		void reduceAttack(unsigned u);
		/*!
		 * \brief Return the number of the given UnitType the player has.
		 * \param type The given UnitType
		 */
		unsigned unit(const UnitType & type) const;
		/*!
		 * \brief Add the given UnitType in the player base.
		 * \param type The given UnitType
		 * \return True if it was added, false if not.
		 */
		bool addUnit(const UnitType & type);
		/*!
		 * \brief Remove the given UnitType in the player base.
		 * \param type The given UnitType
		 * \return True if it was removed, false if not.
		 */
		bool removeUnit(const UnitType & type);
		/*!
		 * \brief Effectues the battle disruption.
		 */
		void disruption();
		/*!
		 * \brief Returns the name of the player
		 * \return The name of the player
		 */
		const std::string & name() const;
		/*!
		 * \brief Returns the total number of unit the player has.
		 */
		unsigned nbUnit() const;
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

	private:
		friend std::ostream & operator<< (std::ostream & out, const Player & in);
};


#endif // PLAYER_H
