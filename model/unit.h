#ifndef UNIT_H
#define UNIT_H

#include <iostream>

#include "unittype.h"
#include "side.h"

class Unit{
		const UnitType type_;
		const Side side_;
		unsigned hp_;
		bool enable_;
	public:
		Unit(UnitType type, Side side);
		void reset();
		unsigned reductHP(unsigned u);

		const UnitType& type() const;
		const Side& side() const;
		unsigned hp() const;
		bool enable() const;
};

std::ostream & operator<< (std::ostream & out, const Unit& in);

#endif // UNIT_H
