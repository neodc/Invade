/*!
* \file dicelabel.h
* \brief Definition of the DiceLabel class.
*/
#ifndef DICELABEL_H
#define DICELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "../model/dicetype.h"

/*!
 * \brief The DiceLabel class
 * A version of QLabel that knows what dice you uses.
 */
class DiceLabel : public QLabel {

		Q_OBJECT
		DiceType type_;

	public:

		/*!
		 * \brief DiceLabel DiceLabel constructor with three parameters.
		 * \param type The type of the dice.
		 * \param size The width and height of the Widget.
		 * \param parent The parent of the Widget.
		 */
		explicit DiceLabel( DiceType type, int size = 64, QWidget * parent = 0 );

		/*!
		 * \brief setType Sets the type of the dice the DiceLabel represents.
		 * \param type The new type of the dice.
		 */
		void setType(DiceType type);

		/*!
		 * \brief type Returns the type of the dice the DiceLabel represents.
		 * \return The type of the dice.
		 */
		DiceType type();

		~DiceLabel();

	signals:

		/*!
		 * \brief leftClicked The signals emitted when someone left clicks the Label.
		 */
		void leftClicked();

		/*!
		 * \brief leftClicked The signals emitted when someone right clicks the Label.
		 */
		void rightClicked();

	protected:

		void mousePressEvent ( QMouseEvent * event) ;
};


#endif // DICELABEL_H
