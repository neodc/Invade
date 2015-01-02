#include "dicelabel.h"

DiceLabel::DiceLabel(DiceType type, int size, QWidget * parent ) : QLabel(parent) {
	type_ = type;
	this->setMaximumSize(QSize(size, size));
	this->setScaledContents(true);
}

DiceLabel::~DiceLabel() {
}


void DiceLabel::setType(DiceType type) {
	type_ = type;
}

DiceType DiceLabel::type() {
	return type_;
}

void DiceLabel::mousePressEvent (QMouseEvent * event) {

	if (event->button() == Qt::RightButton) {
		emit rightClicked();
	} else {
		emit leftClicked();
	}
}
