/*!
* \file effectlabel.h
* \brief Definition of the EffectLabel class.
*/
#ifndef EFFECTLABEL_H
#define EFFECTLABEL_H

#include <QLabel>
#include "../model/effect.h"

/*!
 * \brief The EffectLabel class
 * A version of QLabel that knows what effect you select.
 */
class EffectLabel : public QLabel {

		Q_OBJECT
		Effect type_;

	public:

		/*!
		 * \brief EffectLabel EffectLabel constructor with three parameters.
		 * \param type The Effect the Label holds.
		 * \param text The displayed text of the Label.
		 * \param parent The parent of the Widget.
		 */
		explicit EffectLabel(Effect type, const QString & text = "", QWidget * parent = 0 );

		/*!
		 * \brief setType Sets the Effect the EffectLabel holds.
		 * \param type The new Effect.
		 */
		void setType(Effect type);

		/*!
		 * \brief type Returns the Effect the EffectLabel holds.
		 * \return Return the Effect.
		 */
		Effect type();

		~EffectLabel();

	signals:

		/*!
		 * \brief clicked Signal emitted when someone clicks the Label.
		 */
		void clicked();

	protected:

		void mousePressEvent ( QMouseEvent * ) ;
};


#endif // EFFECTLABEL_H
