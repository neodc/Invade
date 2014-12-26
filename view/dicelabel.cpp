#include "dicelabel.h"

DiceLabel::DiceLabel(DiceType type, const QString& text, QWidget * parent ) : QLabel(parent){
	this->setText(text);
	type_ = type;
}

DiceLabel::~DiceLabel(){
}


void DiceLabel::setType(DiceType type){
	type_ = type;
}

DiceType DiceLabel::type(){
	return type_;
}

void DiceLabel::mousePressEvent ( QMouseEvent * ){
	emit clicked();
}
