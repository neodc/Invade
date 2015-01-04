/*!
* \file unitlabel.h
* \brief Definition of the UnitLabel class.
*/
#ifndef UNITLABEL_H
#define UNITLABEL_H

#include <QLabel>
#include "model/unittype.h"

/*!
 * \brief The UnitLabel class
 * A version of QLabel that knows what UnitType you select.
 */
class UnitLabel : public QLabel {

		Q_OBJECT
		UnitType type_;

	public:

		/*!
		 * \brief UnitLabel UnitLabel constructor with three parameters.
		 * \param type The unit type the Label represents.
		 * \param size The size of the Widget.
		 * \param parent The parent of the Widget.
		 */
		explicit UnitLabel( const UnitType & type, int size = 54, QWidget * parent = 0 );

		/*!
		 * \brief setType Sets the unit type the Label represents.
		 * \param type The new unit type the Label represents.
		 */
		void setType(UnitType type);

		/*!
		 * \brief type Returns the unit type the Label represents.
		 * \return The unit type the Label represents.
		 */
		UnitType type();

		~UnitLabel();

	signals:

		/*!
		 * \brief clicked The signal emitted when someone clicks the Label.
		 */
		void clicked();

	protected:

		void mousePressEvent ( QMouseEvent * ) ;
};


#endif // UNITLABEL_H
