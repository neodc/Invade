#include "invade.h"

Invade::Invade(): current_{Side::NORTH}, winner_{Side::NORTH}, phase_{Phase::NO_PLAYER}{}

const Board & Invade::board() const{ return board_; }
const Player & Invade::player(const Side side){ return players_.at(side); }
const Side Invade::current() const{ return current_; }
const Side Invade::winner() const{ return winner_; }
const Phase Invade::phase() const{ return phase_; }
