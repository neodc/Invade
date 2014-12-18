#ifndef UNITTYPE_H
#define UNITTYPE_H

class UnitType{
	public:
		static const UnitType NORMAL;
		static const UnitType ELITE_A;
		static const UnitType ELITE_B;
		static const UnitType ELITE_C;

	private:
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
};

#endif // UNITTYPE_H
