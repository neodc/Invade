#ifndef DICE_H
#define DICE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>

class Dice{
private:
	unsigned value;
public:
	Dice();
	void roll();
	unsigned getValue();
};

#endif // DICE_H
