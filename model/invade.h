#ifndef INVADE_H
#define INVADE_H

#include "board.h"
#include "side.h"
#include "player.h"
#include "phase.h"
#include "effect.h"
#include "vector"

#include <map>

class Invade{
		Board board_;
		std::map<Side, Player> players_;
		Side current_;
		Side winner_;
		Phase phase_;
		std::vector<Effect> effects_;
		unsigned nbActions_;

	public:
		Invade();
		void begin(const std::string p1, const std::string p2); // start/restart the game.

		void swapDice(const DiceType d1, const DiceType d2);
		void endDice();

		bool choseEffect(Effect effect, UnitType elite = UnitType::NORMAL);
		void endEffect();

		bool move(const Position origin, const Position dest);
		void endMove();

		bool attack(const Position origin, const Position dest, bool bombshell = false);
		void endAttack();

		const Board & board() const;
		const Player & player(const Side side);
		Side current() const;
		Side opponent() const;
		Side winner() const;
		Phase phase() const;

	private:
		void applyEffect(Effect effect, UnitType elite = UnitType::NORMAL);
};

#endif // INVADE_H
