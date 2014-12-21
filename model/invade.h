#ifndef INVADE_H
#define INVADE_H

#include "board.h"
#include "side.h"
#include "player.h"
#include "phase.h"
#include "effect.h"

#include <map>

class Invade{
		Board board_;
		std::map<Side, Player> players_;
		Side current_;
		Side winner_;
		Phase phase_;
		Effect effect1_;
		Effect effect2_;
		unsigned nbMovement_;

	public:
		Invade();
		void begin(const std::string p1, const std::string p2); // start/restart the game.

		void swapDice(const DiceType d1, const DiceType d2);
		void endDice();

		bool choseEffect(unsigned effect1);
		bool choseEffect(unsigned effect1, unsigned effect2);
		bool choseEffect(unsigned effect1, unsigned effect2, UnitType elite);
		void endEffect();

		bool move(const Position origin, const Position dest);
		void endMove();

		bool attack(const Position origin, const Position dest, bool bombshell = false);
		void endAttack();

		const Board & board() const;
		const Player & player(const Side side);
		const Side current() const;
		const Side opponent() const;
		const Side winner() const;
		const Phase phase() const;

	private:
		void applyEffect(unsigned effect);
		void applyEffect(unsigned effect, UnitType elite);
};

#endif // INVADE_H
