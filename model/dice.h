/*!
 * \file dice.h
 * \brief Definition of the Dice class
 */
#ifndef DICE_H
#define DICE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>

/*!
 * \brief The Dice class
 * Manage a invade dice.
 */
class Dice {
	private:
		unsigned value_;
	public:
		/*!
		 * \brief Dice Constructs a Dice.
		 */
		Dice();
		/*!
		 * \brief rolls the dice.
		 */
		void roll();
		/*!
		 * \brief Returns the dice value
		 */
		unsigned value() const;
		/*!
		 * \brief set the value of the dice.
		 * \param value the new value of the dice.
		 */
		void value(unsigned value);
		/*!
		 * \brief reduce the value of the dice, with a minimum dice value of 1.
		 * \param u Value which reduces the dice.
		 */
		void reduce(unsigned u);
};

/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the Dice.
 * \return the output stream.
 */
std::ostream & operator<< (std::ostream & out, const Dice & in);

#endif // DICE_H
