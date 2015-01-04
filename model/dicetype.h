#ifndef DICETYPE_H
#define DICETYPE_H
#include <iostream>
/*!
 * \file dicetype.h
 * \brief Definition of the DiceType enum
 */
enum class DiceType : char {
	ABS, /*! The Abscissa dice*/
	ORD, /*! The Ordinate dice*/
	COM, /*! The Commender dice*/
	EFF, /*! The Effect dice*/
	ATT  /*! The Attack (or defence) dice*/
};

/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the DiceType.
 * \return the output stream.
 */
std::ostream & operator<< (std::ostream & out, const DiceType & in);

#endif // DICETYPE_H
