#include "tilelabel.h"

TileLabel::TileLabel( const QString& text, QWidget * parent ) :
	QLabel(parent){
		this->setScaledContents(true);
		QString path = ":/new/images/boardTile.png";
		this->setPixmap(path);
	//	this->setText(text);
	}

	TileLabel::~TileLabel(){}

	void TileLabel::mousePressEvent ( QMouseEvent * ){
		emit clicked();
	}
