#ifndef EFFECT_H
#define EFFECT_H

#include <iostream>
/*!
 * \file effect.h
 * \brief Definition of the Effect enum
 */
enum class Effect : char {
	NO_EFFECT = 1,			/*! The no effect Effect */
	INCREASED_MOVEMENT = 2,	/*! The increased movement Effect */
	INCREMENT_SOLDIER = 3,	/*! The increment soldier Effect */
	IMPROVED_ATTACK = 4,	/*! The improved attacks Effect */
	CHANGE_SOLDIER = 5,		/*! The promote soldier Effect */
	TWO_EFFECTS = 6			/*! when he can chose two effect other effect Effect */
};

/*!
 * \brief Operator<< overload
 * \param out The output stream.
 * \param in The Effect.
 * \return The output stream.
 */
std::ostream & operator<< (std::ostream & out, const Effect & in);

/**
 * @brief Operator < overload
 * @param first An int
 * @param second An effect
 * @return True if first is smaller than second, false otherwise.
 */
bool operator<(const int first, const Effect & second);
/**
 * @brief Operator > overload
 * @param first An int
 * @param second An effect
 * @return True if first is higher than second, false otherwise.
 */
bool operator>(const int first, const Effect & second);
/**
 * @brief Operator <= overload
 * @param first An int
 * @param second An effect
 * @return True if first is smaller or equal than second, false otherwise.
 */
bool operator<=(const int first, const Effect & second);
/**
 * @brief Operator >= overload
 * @param first An int
 * @param second An effect
 * @return True if first is higher or equal than second, false otherwise.
 */
bool operator>=(const int first, const Effect & second);
/**
 * @brief Operator == overload
 * @param first An int
 * @param second An effect
 * @return True if first is equal to second, false otherwise.
 */
bool operator==(const int first, const Effect & second);
/**
 * @brief Operator != overload
 * @param first An int
 * @param second An effect
 * @return True if first is not equal to second, false otherwise.
 */
bool operator!=(const int first, const Effect & second);


/**
 * @brief Operator < overload
 * @param first An effect
 * @param second An int
 * @return True if first is smaller than second
 */
bool operator<(const Effect & first, const int second);
/**
 * @brief Operator > overload
 * @param first An effect
 * @param second An int
 * @return True if first is higher than second
 */
bool operator>(const Effect & first, const int second);
/**
 * @brief Operator <= overload
 * @param first An effect
 * @param second An int
 * @return True if first is smaller or equal than second
 */
bool operator<=(const Effect & first, const int second);
/**
 * @brief Operator >= overload
 * @param first An effect
 * @param second An int
 * @return True if first is higher or equal than second
 */
bool operator>=(const Effect & first, const int second);
/**
 * @brief Operator == overload
 * @param first An effect
 * @param second An int
 * @return True if first is equal to second
 */
bool operator==(const Effect & first, const int second);
/**
 * @brief Operator != overload
 * @param first An effect
 * @param second An int
 * @return True if first is not equal to second
 */
bool operator!=(const Effect & first, const int second);

#endif // EFFECT_H
