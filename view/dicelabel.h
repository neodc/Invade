#ifndef DICELABEL_H
#define DICELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "../model/dicetype.h"

class DiceLabel : public QLabel {

		Q_OBJECT
		DiceType type_;

	public:
		explicit DiceLabel( DiceType type, int size = 64, QWidget * parent = 0 );
		void setType(DiceType type);
		DiceType type();
		~DiceLabel();

	signals:
		void leftClicked();
		void rightClicked();

	protected:
		void mousePressEvent ( QMouseEvent * event) ;
};


#endif // DICELABEL_H
