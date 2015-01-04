#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include <QString>

typedef struct {
	unsigned x; /*! The abscissa of the point*/
	unsigned y; /*! The ordinate of the point*/
} Position;

/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the Position.
 * \return the output stream.
 */
std::ostream & operator<< (std::ostream & out, const Position & in);

/*!
 * \brief Transform a Position into a QString.
 * \param pos A Position.
 * \return A QString.
 */
QString pos2str(const Position & pos);/*!
 * \brief Transform a QString into a Position.
 * \param pos A QString.
 * \return A Position.
 */
Position str2pos(const QString & s);

/**
 * @brief operator < overload
 * @param first a Position
 * @param second a Position
 * @return true if first is smaller than second
 */
bool operator<(const Position & first, const Position & second);

/**
 * @brief operator == overload
 * @param first a Position
 * @param second a Position
 * @return true if first is equal to second
 */
bool operator==(const Position & first, const Position & second);
/**
 * @brief operator != overload
 * @param first a Position
 * @param second a Position
 * @return true if first is not equal to second
 */
bool operator!=(const Position & first, const Position & second);

#endif // POSITION_H
