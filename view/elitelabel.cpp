#include "elitelabel.h"

EliteLabel::EliteLabel(Unit type, int size, QWidget * parent ) : QLabel(parent) {
	this->setMaximumSize(QSize(size, size));
	this->setScaledContents(true);
	type_ = type;
}

EliteLabel::~EliteLabel() {
}


void EliteLabel::setType(Unit type) {
	type_ = type;
}

Unit EliteLabel::type() {
	return type_;
}

void EliteLabel::mousePressEvent ( QMouseEvent * ) {
	emit clicked();
}
