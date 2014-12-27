#include "elitelabel.h"

EliteLabel::EliteLabel(Unit type, const QString& text, QWidget * parent ) : QLabel(parent){
	this->setText(text);
	type_ = type;
}

EliteLabel::~EliteLabel(){
}


void EliteLabel::setType(Unit type){
	type_ = type;
}

Unit EliteLabel::type(){
	return type_;
}

void EliteLabel::mousePressEvent ( QMouseEvent * ){
	emit clicked();
}
