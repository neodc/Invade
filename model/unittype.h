#ifndef UNITTYPE_H
#define UNITTYPE_H

#include <iostream>

class UnitType{
	public:
		static const UnitType NORMAL;
		static const UnitType ELITE_A;
		static const UnitType ELITE_B;
		static const UnitType ELITE_C;

	private:
		static unsigned nextId_;
		unsigned id_;
		unsigned hpMax_;
		int speed_;
		int accuracy_;
		bool elite_;
		unsigned bombshell_;

	private:
		UnitType(unsigned pvMax, int speed, int accuracy, bool elite, unsigned bombshell);

	public:
		unsigned hpMax() const;
		int speed() const;
		int accuracy() const;
		bool elite() const;
		unsigned bombshell() const;
		bool operator==(const UnitType& other) const;
		bool operator!=(const UnitType& other) const;
		bool operator<(const UnitType& other) const;
};

std::ostream & operator<<(std::ostream & out, const UnitType& in);

#endif // UNITTYPE_H
