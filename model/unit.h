#ifndef UNIT_H
#define UNIT_H

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

		const UnitType& type();
		const Side& side();
		unsigned hp();
		bool enable();
};

#endif // UNIT_H
