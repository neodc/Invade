#ifndef INVADE_H
#define INVADE_H

#include "board.h"
#include "side.h"
#include "player.h"
#include "phase.h"

#include <map>

class Invade{
		Board board_;
		std::map<Side, Player> players_;
		Side current_;
		Side winner_;
		Phase phase_;

	public:
		Invade();
		void begin(const std::string p1, const std::string p2); // start/restart the game.

		void swapDice(const DiceType d1, const DiceType d2);

		bool choseEffect(unsigned effect); // TODO enum?

		bool move(const Position origin, const Position dest);
		void endMove();

		bool attack(const Position origin, const Position dest);
		void endAttack();

		const Board & board() const;
		const Player & player(const Side side);
		const Side current() const;
		const Side winner() const;
		const Phase phase() const;
};

#endif // INVADE_H
