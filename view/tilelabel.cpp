#include "tilelabel.h"

TileLabel::TileLabel( const QString& text, QWidget * parent ) :
	QLabel(parent){
		this->setMinimumSize(QSize(32,32));
		this->setScaledContents(true);
		this->setPixmap(Images::tile());
	//	this->setText(text);
	}

	TileLabel::~TileLabel(){}

	void TileLabel::mousePressEvent (QMouseEvent * event){

		if (event->button() == Qt::RightButton){
			emit rightClicked();
		} else {
			emit leftClicked();
		}
	}
