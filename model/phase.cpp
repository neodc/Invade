#include "phase.h"

std::ostream & operator<< ( std::ostream & out, Phase in){
    switch (in){
    case Phase::NO_PLAYER:
        out << "no player";
        break;
    case Phase::PLAYING:
        out << "playing";
        break;
    case Phase::END:
        out << "end";
        break;
    }
    return out;
}
