#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>

#include "dicetype.h"
#include "dice.h"
#include "unittype.h"

class Player{
		const std::string name_;
		std::map<const DiceType, Dice> dice_;
		std::map<const UnitType, unsigned> units_;
	public:
		Player(std::string name);

		unsigned dice(const DiceType &type) const;
		void swapDice(const DiceType &t1, const DiceType &t2);
		void swapDice(const DiceType &t1, const DiceType &t2, const DiceType &t3);
		void rollDice();
		void reductAttack(unsigned u);
		unsigned unit(const UnitType &type) const;
		bool addUnit(const UnitType &type);

		const std::string& name() const;

	private:
		unsigned nbUnit() const;
		friend std::ostream & operator<< (std::ostream & out, const Player& in);
};


#endif // PLAYER_H
