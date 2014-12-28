#include "images.h"

QImage Images::tile_{":/new/images/boardTile.png"};

QImage Images::pawn_{":/new/images/pawn.png"};
QImage Images::A_{":/new/images/A.png"};
QImage Images::B_{":/new/images/B.png"};
QImage Images::Bbomb_{":/new/images/Bbomb.png"};
QImage Images::C_{":/new/images/C.png"};

std::map<unsigned, QImage> Images::dice_ = {
	{1, QImage(":/new/images/1.png")},
	{2, QImage(":/new/images/2.png")},
	{3, QImage(":/new/images/3.png")},
	{4, QImage(":/new/images/4.png")},
	{5, QImage(":/new/images/5.png")},
	{6, QImage(":/new/images/6.png")},
};

std::map<unsigned, QImage> Images::effArrows_ = {
	{1, QImage(":/new/images/ea1.png")},
	{2, QImage(":/new/images/ea2.png")},
	{3, QImage(":/new/images/ea3.png")},
	{4, QImage(":/new/images/ea4.png")},
	{5, QImage(":/new/images/ea5.png")},
	{6, QImage(":/new/images/ea6.png")},
};


QPixmap Images::tile(bool selected){
	QPixmap pix;
	if (selected){
		pix.convertFromImage(changeImage(tile_, 0, 0, -50));
	}else{
		pix.convertFromImage(tile_);
	}
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
