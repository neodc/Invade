#ifndef PHASE_H
#define PHASE_H
#include <iostream>

enum class Phase : char{
	NO_PLAYER,
	PLAYING,
	END
};

std::ostream & operator<< (std::ostream & out, Phase in);

#endif // PHASE_H
