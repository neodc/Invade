#include "images.h"

QImage Images::tile_;

QImage Images::pawn_;
QImage Images::A_;
QImage Images::B_;
QImage Images::Bbomb_;
QImage Images::C_;

std::map<unsigned, QImage> Images::dice_;

std::map<unsigned, QImage> Images::effArrows_;

void Images::reload(){
	tile_.load(":/new/images/boardTile.png");

	pawn_.load(":/new/images/pawn.png");
	A_.load(":/new/images/A.png");
	B_.load(":/new/images/B.png");
	Bbomb_.load(":/new/images/Bbomb.png");
	C_.load(":/new/images/C.png");

	for( unsigned i = 1; i <= 6; ++i ){
		dice_[i].load( QString(":/new/images/%1.png").arg(i) );
	}

	for( unsigned i = 1; i <= 6; ++i ){
		effArrows_[i].load( QString(":/new/images/ea%1.png").arg(i) );
	}
}

QPixmap Images::tile(bool selected){
	QPixmap pix;
	if (selected){
		pix.convertFromImage(changeImage(tile_, 0, 0, -50));
	}else{
		pix.convertFromImage(tile_);
	}
	return pix;
}

QPixmap Images::tile(Unit unit, bool tileSelected, bool unitSelected){
	QPixmap pixTile(tile(tileSelected));
	QPixmap pixPawn(pawn(unit, unitSelected));
	QPixmap pix = QPixmap(pixTile.size());
	QPainter painter(&pix);

	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(pix.rect(), Qt::transparent);

	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawPixmap(0, 0, pixTile);

	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawPixmap(10, 10, pixPawn);

	painter.end();

	return pix;
}

QPixmap Images::pawn(UnitType type, bool selected, Side side){
	QPixmap pix;

	QImage tmp;
	if (type == UnitType::NORMAL){
		tmp = pawn_;
	} else if(type == UnitType::ELITE_A){
		tmp = A_;
	} else if(type == UnitType::ELITE_B){
		tmp = B_;
	} else if(type == UnitType::ELITE_C){
		tmp = C_;
	}

	if(selected){
		pix.convertFromImage(changeImage(tmp, 0, 0, -50));
	} else {
		switch (side){
		case Side::NORTH:
			pix.convertFromImage(changeImage(tmp, -200, -200, 0));
			break;
		case Side::SOUTH:
			pix.convertFromImage(changeImage(tmp, -63, -255, -63));
		}
	}

	return pix;
}

QPixmap Images::pawn(Unit unit, bool selected){
	QPixmap pix;

	QImage tmp;
	if (unit.type() == UnitType::NORMAL){
		tmp = pawn_;
	} else if(unit.type() == UnitType::ELITE_A){
		tmp = A_;
	} else if(unit.type() == UnitType::ELITE_B && unit.bombshell() == 0){
		tmp = B_;
	} else if(unit.bombshell() >= 1){
		tmp = Bbomb_;
	} else if(unit.type() == UnitType::ELITE_C){
		tmp = C_;
	}

	if (selected){
		pix.convertFromImage(changeImage(tmp, 0, 0, -50));
	} else if (!unit.enable()){
		pix.convertFromImage(changeImage(tmp, -150, -150, -150));
	} else if (unit.hp() < 2){
		pix.convertFromImage(changeImage(tmp, -50, -200, -200));
	} else {
		switch (unit.side()){
		case Side::NORTH:
			pix.convertFromImage(changeImage(tmp, -200, -200, 0));
			break;
		case Side::SOUTH:
			pix.convertFromImage(changeImage(tmp, -63, -255, -63));
		}
	}

	return pix;
}

QPixmap Images::dice(unsigned value, bool selected){
	QPixmap pix;
	if(selected){
		pix.convertFromImage(changeImage(dice_.at(value), 0, 0, -50));
	} else {
		pix.convertFromImage(dice_.at(value));
	}
	return pix;
}

QPixmap Images::effArrows(unsigned value){
	QPixmap pix;
	pix.convertFromImage(effArrows_.at(value));
	return pix;
}


QImage Images::changeImage(QImage origin, int dr, int dg, int db){
	QImage newImage(origin.width(), origin.height(), QImage::Format_ARGB32);
	QColor oldColor;
	int r,g,b,a;

	for(int x=0; x<newImage.width(); x++){
		for(int y=0; y<newImage.height(); y++){

				oldColor = QColor::fromRgba(origin.pixel(x,y));
				r = oldColor.red() + dr;
				g = oldColor.green() + dg;
				b = oldColor.blue() + db;
				a = oldColor.alpha();
				//we check if the new values are between 0 and 255
				r = qBound(0, r, 255);
				g = qBound(0, g, 255);
				b = qBound(0, b, 255);

				newImage.setPixel(x,y, qRgba(r,g,b,a));
		}
	}
	return newImage;
}
