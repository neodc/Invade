#include "dicelabel.h"

DiceLabel::DiceLabel(DiceType type, const QString& text, QWidget * parent ) : QLabel(parent){
	this->setText(text);
	type_ = type;
	this->setMaximumSize(QSize(64,64));
	this->setScaledContents(true);
}

DiceLabel::~DiceLabel(){
}


void DiceLabel::setType(DiceType type){
	type_ = type;
}

DiceType DiceLabel::type(){
	return type_;
}

void DiceLabel::mousePressEvent (QMouseEvent * event){

	if (event->button() == Qt::RightButton){
		emit rightClicked();
	}
	emit leftClicked();
}
