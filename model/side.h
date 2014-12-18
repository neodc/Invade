#ifndef SIDE_H
#define SIDE_H
#include <iotream>

enum class Side : char{
    NORTH,
    SOUTH
};

std::ostream & operator<< (std::ostream & out, Side in);

#endif // SIDE_H
