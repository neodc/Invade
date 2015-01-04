/*!
 * \file phase.h
 * \brief Definition of the Phase enum
 */
#ifndef PHASE_H
#define PHASE_H
#include <iostream>

/*!
 * \brief The Phase enum
 * Represents the phases of a invade game.
 */
enum class Phase : char {
	NO_PLAYER,			/*! The phase where there is no players*/
	PLAYING_DICE,		/*! The phase where we must place the dices*/
	PLAYING_EFFECT,		/*! The phase where we must choose our effects*/
	PLAYING_MOVE,		/*! The phase where we must move or add our units*/
	PLAYING_COMMANDER,	/*! The phase where we must move the unit moved by the commander*/
	PLAYING_ATTACK,		/*! The phase where we must attacks*/
	END					/*! The phase where the game has ended*/
};

/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the Phase.
 * \return the output stream.
 */
std::ostream & operator<< (std::ostream & out, const Phase & in);
/*!
 * \brief Tells the next phase.
 * \param phase A phase.
 * \return The next phase.
 */
Phase next(Phase phase);

#endif // PHASE_H
