#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <QJsonObject>

#include "unittype.h"
#include "side.h"

class Unit{
		UnitType type_;
		Side side_;
		unsigned hp_;
		bool enable_;
		unsigned bombshell_;
	public:
		Unit(UnitType type = UnitType::NORMAL, Side side = Side::NORTH);
		void reset();
		unsigned reduceHP(unsigned u);
		unsigned reduceBombshell(unsigned u);

		const UnitType& type() const;
		const Side& side() const;
		unsigned hp() const;
		unsigned bombshell() const;
		bool enable() const;
		void disable();
		void read(const QJsonObject &json);
		void write(QJsonObject &json) const;
};

std::ostream & operator<< (std::ostream & out, const Unit& in);

#endif // UNIT_H
