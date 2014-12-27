#include "elitelabel.h"

EliteLabel::EliteLabel(Unit type, QPixmap pix, QWidget * parent ) : QLabel(parent){
	this->setScaledContents(true);
	this->setPixmap(pix);
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
