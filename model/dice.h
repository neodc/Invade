#ifndef DICE_H
#define DICE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>

class Dice{
private:
	unsigned value_;
public:
	Dice();
	void roll();
	unsigned value() const;
	void value(unsigned value);
	void reduce(unsigned u);
};

std::ostream & operator<< (std::ostream & out, const Dice& in);

#endif // DICE_H
