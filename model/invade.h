#ifndef INVADE_H
#define INVADE_H

#include "board.h"
#include "side.h"
#include "player.h"
#include "phase.h"
#include "effect.h"

#include <map>
#include <set>

class Invade{
		Board board_;
		std::map<Side, Player> players_;
		Side current_;
		Side winner_;
		Phase phase_;
		std::set<Effect> effects_;
		unsigned nbActions_;

	public:
		Invade();
		void begin(const std::string p1, const std::string p2); // start/restart the game.

		bool endPhase();

		void swapDice(const DiceType d1, const DiceType d2);

		bool chooseEffect(Effect effect, UnitType elite = UnitType::NORMAL);

		bool move(const Position origin, const Position dest);
		bool addUnit(const Position p, const UnitType type);

		bool attack(const Position origin, const Position dest, bool bombshell = false);

		const Board & board() const;
		const Player & player(const Side side) const;
		Side current() const;
		Side winner() const;
		Phase phase() const;

	private:
		void applyEffect(Effect effect, UnitType elite = UnitType::NORMAL);
		Player & player(const Side side);
		bool hasEffect(Effect e) const;
		bool isVictory();
};

#endif // INVADE_H
