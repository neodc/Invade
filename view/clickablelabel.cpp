#include "clickablelabel.h"

ClickableLabel::ClickableLabel( const QString& text, QWidget * parent ) :
	QLabel(parent){
	//	this->setScaledContents(true);
	//	QString path = ":/new/images/boardTile.png";
	//	this->setPixmap(path);
		this->setText(text);
	}

	ClickableLabel::~ClickableLabel(){}

	void ClickableLabel::mousePressEvent ( QMouseEvent * ){
		emit clicked();
	}
