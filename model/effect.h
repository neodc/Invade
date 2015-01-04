#ifndef EFFECT_H
#define EFFECT_H

#include <iostream>

enum class Effect : char {
	NO_EFFECT = 1,			/*! The no effect Effect */
	INCREASED_MOVEMENT = 2,	/*! The increased movement Effect */
	INCREMENT_SOLDIER = 3,	/*! The increment soldier Effect */
	IMPROVED_ATTACK = 4,	/*! The improved attacks Effect */
	CHANGE_SOLDIER = 5,		/*! The promote soldier Effect */
	TWO_EFFECTS = 6			/*! when he can chose two effect other effect Effect */
};

/*!
 * \brief operator<< overload
 * \param out the output stream.
 * \param in the Effect.
 * \return the output stream.
 */
std::ostream & operator<< (std::ostream & out, const Effect & in);

/**
 * @brief operator < overload
 * @param first an int
 * @param second an effect
 * @return true if first is smaller than second
 */
bool operator<(const int first, const Effect & second);
/**
 * @brief operator > overload
 * @param first an int
 * @param second an effect
 * @return true if first is higher than second
 */
bool operator>(const int first, const Effect & second);
/**
 * @brief operator <= overload
 * @param first an int
 * @param second an effect
 * @return true if first is smaller or equal than second
 */
bool operator<=(const int first, const Effect & second);
/**
 * @brief operator >= overload
 * @param first an int
 * @param second an effect
 * @return true if first is higher or equal than second
 */
bool operator>=(const int first, const Effect & second);
/**
 * @brief operator == overload
 * @param first an int
 * @param second an effect
 * @return true if first is equal to second
 */
bool operator==(const int first, const Effect & second);
/**
 * @brief operator != overload
 * @param first an int
 * @param second an effect
 * @return true if first is not equal to second
 */
bool operator!=(const int first, const Effect & second);


/**
 * @brief operator < overload
 * @param first an effect
 * @param second an int
 * @return true if first is smaller than second
 */
bool operator<(const Effect & first, const int second);
/**
 * @brief operator > overload
 * @param first an effect
 * @param second an int
 * @return true if first is higher than second
 */
bool operator>(const Effect & first, const int second);
/**
 * @brief operator <= overload
 * @param first an effect
 * @param second an int
 * @return true if first is smaller or equal than second
 */
bool operator<=(const Effect & first, const int second);
/**
 * @brief operator >= overload
 * @param first an effect
 * @param second an int
 * @return true if first is higher or equal than second
 */
bool operator>=(const Effect & first, const int second);
/**
 * @brief operator == overload
 * @param first an effect
 * @param second an int
 * @return true if first is equal to second
 */
bool operator==(const Effect & first, const int second);
/**
 * @brief operator != overload
 * @param first an effect
 * @param second an int
 * @return true if first is not equal to second
 */
bool operator!=(const Effect & first, const int second);

#endif // EFFECT_H
