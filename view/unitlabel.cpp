#include "unitlabel.h"

UnitLabel::UnitLabel(const UnitType &type, int size, QWidget * parent ) : QLabel(parent), type_(type) {
	this->setMaximumSize(QSize(size, size));
	this->setScaledContents(true);
}

UnitLabel::~UnitLabel() {
}


void UnitLabel::setType(UnitType type) {
	type_ = type;
}

UnitType UnitLabel::type() {
	return type_;
}

void UnitLabel::mousePressEvent ( QMouseEvent * ) {
	emit clicked();
}
