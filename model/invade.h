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

/*!
 * \brief The Invade class
 */
class Invade : public SujetDObservation {
		Board board_;
		std::map<Side, Player> players_;
		Side current_;
		Side winner_;
		Phase phase_;
		std::set<Effect> effects_;
		unsigned nbActions_;
		Position commander_;

	public:
		/*!
		 * \brief Constructs an invade game
		 */
		Invade();
		/*!
		 * \brief Resets the game.
		 */
		void reset();

		/*!
		 * \brief Start/restart the game.
		 * \param p1 The name of the first player.
		 * \param p2 The name of the second player.
		 */
		void begin(const std::string p1, const std::string p2);

		/*!
		 * \brief Tells if we can end the phase.
		 * \return True if we can end, false if not.
		 */
		bool canEndPhase() const;

		/*!
		 * \brief End the phase.
		 * \return True if the phase has ended, false if not.
		 */
		bool endPhase();

		/*!
		 * \brief Swaps two dices.
		 * \param d1 the first dice.
		 * \param d2 the second dice.
		 */
		void swapDice(const DiceType d1, const DiceType d2);

		/*!
		 * \brief Tells if we can choose an effect.
		 * \param effect The chosen effect
		 * \param elite The elite needed by certains effects.
		 * \return True if we can choose an effect, false if not.
		 */
		bool canChooseEffect(Effect effect, UnitType elite = UnitType::NORMAL) const;
		/*!
		 * \brief Choose an effect to apply.
		 * \param effect The chosen effect
		 * \param elite The elite needed by certains effects.
		 * \return True if the effect has applied, false if not.
		 */
		bool chooseEffect(Effect effect, UnitType elite = UnitType::NORMAL);

		/*!
		 * \brief Tells if the unit can move.
		 * \param origin the original position of the unit.
		 * \param dest the destination of the unit.
		 * \return True if the unit can move, false if not.
		 */
		bool canMove(const Position origin, const Position dest) const;
		/*!
		 * \brief Moves the unit.
		 * \param origin the original position of the unit.
		 * \param dest the destination of the unit.
		 * \return True if the unit has moved, false if not.
		 */
		bool move(const Position origin, const Position dest);
		/*!
		 * \brief Tells if we can add a unit in the board.
		 * \param p the position where we want to add the unit
		 * \param type the unit.
		 * \return True if we can add a unit, false if not.
		 */
		bool canAddUnit(const Position p, const UnitType type) const;
		/*!
		 * \brief Add a unit in the board.
		 * \param p the position where we want to add the unit
		 * \param type the unit.
		 * \return True if the unit was added, false if not.
		 */
		bool addUnit(const Position p, const UnitType type);

		/*!
		 * \brief Tells if the unit moved by the commander can move.
		 * \param origin the original position of the unit.
		 * \param dest the destination of the unit.
		 * \return True if the unit can move, false if not.
		 */
		bool canMoveCommander(const Position origin, const Position dest) const;
		/*!
		 * \brief Moves the unit moved by the commander.
		 * \param origin the original position of the unit.
		 * \param dest the destination of the unit.
		 * \return True if the unit has moved, false if not.
		 */
		bool moveCommander(const Position origin, const Position dest);
		/*!
		 * \brief Tells if the unit can attack.
		 * \param origin the original position of the unit.
		 * \param dest attacked unit.
		 * \param bombshell Tells if the attack is a bombshell or not
		 * \return True if the unit can attack, false if not.
		 */
		bool canAttack(const Position origin, const Position dest, bool bombshell = false) const;
		/*!
		 * \brief Effectues the attack.
		 * \param origin the original position of the unit.
		 * \param dest attacked unit.
		 * \param bombshell Tells if the attack is a bombshell or not
		 * \return True if attack has succeed, false if not.
		 */
		bool attack(const Position origin, const Position dest, bool bombshell = false);

		/*!
		 * \brief Returns the board. Can't modify this board.
		 * \return The board
		 */
		const Board & board() const;
		/*!
		 * \brief Returns the player at the given Side. Can't modify this player.
		 * \param side The given Side
		 * \return The player
		 */
		const Player & constPlayer(const Side side) const;
		/*!
		 * \brief Tells if the effect has applied this turn.
		 * \param e The effect.
		 * \return True the effect was applied, false if not.
		 */
		bool hasEffect(Effect e) const;
		/*!
		 * \brief Returns the effect list. Can't modify this list.
		 * \return The effect list.
		 */
		const std::set<Effect> effects() const;
		/*!
		 * \brief Returns the current player.
		 * \return The current player.
		 */
		Side current() const;
		/*!
		 * \brief Returns the winner.
		 * \return The winner.
		 */
		Side winner() const;
		/*!
		 * \brief Returns the current phase.
		 * \return The current phase.
		 */
		Phase phase() const;
		/*!
		 * \brief nbActions Retuns the number of remaining actions of the phase.
		 */
		unsigned nbActions() const;
		void read(const QJsonObject & json);
		void write(QJsonObject & json) const;

	private:
		void applyEffect(Effect effect, UnitType elite = UnitType::NORMAL);
		Player & player(const Side side);
		bool isVictory();
};

#endif // INVADE_H
