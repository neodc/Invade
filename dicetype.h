#ifndef DICETYPE_H
#define DICETYPE_H

enum class DiceType : char{
    ABS,
    ORD,
    COM,
    EFF,
    ATT
};

std::ostream & operator<< (std::ostream & out, DiceType in);

#endif // DICETYPE_H
