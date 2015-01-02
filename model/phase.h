#ifndef PHASE_H
#define PHASE_H
#include <iostream>

enum class Phase : char {
	NO_PLAYER,
	PLAYING_DICE,
	PLAYING_EFFECT,
	PLAYING_MOVE,
	PLAYING_COMMANDER,
	PLAYING_ATTACK,
	END
};

std::ostream & operator<< (std::ostream & out, const Phase & in);

Phase next(Phase phase);

#endif // PHASE_H
