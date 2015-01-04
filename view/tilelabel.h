/*!
* \file tilelabel.h
* \brief Definition of the TileLabel class.
*/
#ifndef TILELABEL_H
#define TILELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "view/images.h"

/*!
 * \brief The TileLabel class.
 * A version of QLabel bettered to fit the needs of the game.
 */
class TileLabel : public QLabel {

		Q_OBJECT

	public:

		/*!
		 * \brief TileLabel TileLabel constructor with one parameter.
		 * \param parent The parent of the Widget.
		 */
		explicit TileLabel(QWidget * parent = 0 );

		~TileLabel();

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


#endif // TILELABEL_H
