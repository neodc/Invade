#ifndef UNITTYPE_H
#define UNITTYPE_H

#include <iostream>

class UnitType {
	public:
		static const UnitType NORMAL;	/*! A normal soldier */
		static const UnitType ELITE_A;	/*! A crouched unit */
		static const UnitType ELITE_B;	/*! A bomber man */
		static const UnitType ELITE_C;	/*! A commander unit */

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
		/*!
		 * \brief Returns the max HP of this unit type
		 */
		unsigned hpMax() const;
		/*!
		 * \brief Returns the speed of this unit type
		 * \return The speed of this unit type
		 */
		int speed() const;
		/*!
		 * \brief Returns the accuracy of this unit type
		 * \return The accuracy of this unit type
		 */
		int accuracy() const;
		/*!
		 * \brief Tells if this unit type is a elite or not.
		 * \return True if this unit type is a elite, false if not.
		 */
		bool elite() const;
		/*!
		 * \brief Returns this unit type max Bomshells.
		 */
		unsigned bombshell() const;
		/*!
		 * \brief Returns this unit type max id.
		 */
		unsigned id() const;

		/**
		 * @brief operator == overload.
		 * @param other An other unit type.
		 * @return True if this unit type is equal to the other unit type, false if not.
		 */
		bool operator==(const UnitType & other) const;
		/**
		 * @brief operator == overload.
		 * @param other An other unit type.
		 * @return True if this unit type is not equal to the other unit type, false if not.
		 */
		bool operator!=(const UnitType & other) const;
		/**
		 * @brief Operator < overload
		 * @param other An other unit type.
		 * @return True if this unit type is smaller than the other unit type, false if not.
		 */
		bool operator<(const UnitType & other) const;

		/*!
		 * \brief Returns the unit type matching the given id.
		 * \param i The given id.
		 * \return The related unit type.
		 */
		static const UnitType & fromId(unsigned i);
};
/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the UnitType.
 * \return the output stream.
 */
std::ostream & operator<<(std::ostream & out, const UnitType & in);

#endif // UNITTYPE_H
