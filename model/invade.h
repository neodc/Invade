#ifndef INVADE_H
#define INVADE_H

#include "board.h"
#include "side.h"
#include "player.h"
#include "phase.h"
#include "effect.h"
#include "view/sujetDObservation.h"

#include <map>
#include <set>
#include <QJsonObject>

class Invade : public SujetDObservation{
		Board board_;
		std::map<Side, Player> players_;
		Side current_;
		Side winner_;
		Phase phase_;
		std::set<Effect> effects_;
		unsigned nbActions_;
		Position commander_;

	public:
		Invade();
		void reset();

		void begin(const std::string p1, const std::string p2); // start/restart the game.

		bool canEndPhase() const;
		bool endPhase();

		void swapDice(const DiceType d1, const DiceType d2);

		bool canChooseEffect(Effect effect, UnitType = UnitType::NORMAL) const;
		bool chooseEffect(Effect effect, UnitType elite = UnitType::NORMAL);

		bool canMove(const Position origin, const Position dest) const;
		bool move(const Position origin, const Position dest);
		bool canAddUnit(const Position p, const UnitType type) const;
		bool addUnit(const Position p, const UnitType type);

		bool canMoveCommander(const Position origin, const Position dest) const;
		bool moveCommander(const Position origin, const Position dest);

		bool canAttack(const Position origin, const Position dest, bool bombshell = false) const;
		bool attack(const Position origin, const Position dest, bool bombshell = false);

		const Board & board() const;
		const Player & constPlayer(const Side side) const;
		Side current() const;
		Side winner() const;
		Phase phase() const;
		void read(const QJsonObject &json);
		void write(QJsonObject &json) const;

	private:
		void applyEffect(Effect effect, UnitType elite = UnitType::NORMAL);
		Player & player(const Side side);
		bool hasEffect(Effect e) const;
		bool isVictory();
};

#endif // INVADE_H
