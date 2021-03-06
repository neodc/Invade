/*!
 * \file side.h
 * \brief Definition of the Side enum
 */
#ifndef SIDE_H
#define SIDE_H
#include <iostream>

/*!
 * \brief The Side enum
 * Represent a side where the invade players can be.
 */
enum class Side : char {
	NORTH, /*! The north side */
	SOUTH  /*! The south side */
};

/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the Side.
 * \return the output stream.
 */
std::ostream & operator<< (std::ostream & out, const Side & in);
/*!
 * \brief Return the opposite side of the given side.
 * \param s The given side.
 * \return The opposite side
 */
Side operator!(Side s);

#endif // SIDE_H
