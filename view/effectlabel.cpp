#include "effectlabel.h"

EffectLabel::EffectLabel(Effect type, const QString & text, QWidget * parent ) : QLabel(parent), type_(type) {
	this->setText(text);
}

EffectLabel::~EffectLabel() {
}

void EffectLabel::setType(Effect type) {
	type_ = type;
}

Effect EffectLabel::type() {
	return type_;
}

void EffectLabel::mousePressEvent ( QMouseEvent * ) {
	emit clicked();
}
