#ifndef ELITELABEL_H
#define ELITELABEL_H

#include <QLabel>
#include "../model/unit.h"

class EliteLabel : public QLabel {

		Q_OBJECT
		Unit type_;

	public:
		explicit EliteLabel(Unit type, int size = 54, QWidget * parent = 0 );
		void setType(Unit type);
		Unit type();
		~EliteLabel();

	signals:
		void clicked();

	protected:
		void mousePressEvent ( QMouseEvent * ) ;
};


#endif // ELITELABEL_H
