#include "phase.h"

std::ostream & operator<< ( std::ostream & out, const Phase & in) {

	switch (in) {
		case Phase::NO_PLAYER:
			out << "no player";
			break;
		case Phase::PLAYING_DICE:
			out << "playing dice";
			break;
		case Phase::PLAYING_EFFECT:
			out << "playing effect";
			break;
		case Phase::PLAYING_MOVE:
			out << "playing move";
			break;
		case Phase::PLAYING_COMMANDER:
			out << "playing commander";
			break;
		case Phase::PLAYING_ATTACK:
			out << "playing attack";
			break;
		case Phase::END:
			out << "end";
			break;
	}
	return out;
}

Phase next(Phase phase) {
	switch (phase) {
		case Phase::PLAYING_DICE:
			return Phase::PLAYING_EFFECT;
			break;
		case Phase::PLAYING_EFFECT:
			return Phase::PLAYING_MOVE;
			break;
		case Phase::PLAYING_MOVE:
			return Phase::PLAYING_ATTACK;
			break;
		case Phase::PLAYING_COMMANDER:
			return Phase::PLAYING_MOVE;
			break;
		case Phase::PLAYING_ATTACK:
			return Phase::PLAYING_DICE;
			break;
		default:
			return phase;
			break;
	}
}
