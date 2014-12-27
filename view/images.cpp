#include "images.h"

QImage Images::tile_{":/new/images/boardTile.png"};

QImage Images::pawn_{":/new/images/pawn.png"};

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

QPixmap Images::pawn(UnitType type, Side side, bool selected, bool damaged){
	QPixmap pix;

	if(selected){
		pix.convertFromImage(changeImage(pawn_, 0, 0, -50));
	} else if(damaged){
		pix.convertFromImage(changeImage(pawn_, 0, -100, -100));
	} else {
		switch (side){
		case Side::NORTH:
			pix.convertFromImage(changeImage(pawn_, -200, -200, 0));
			break;
		case Side::SOUTH:
			pix.convertFromImage(changeImage(pawn_, -63, -255, -63));
		}
	}

	if (type != UnitType::NORMAL){
		QPixmap result(pix.width(), pix.height());
		QPixmap overlay;

		if(type == UnitType::ELITE_A){
			overlay.load(":new/images/A.png");
		} else if (type == UnitType::ELITE_B){
			overlay.load(":new/images/B.png");
		} else if (type == UnitType::ELITE_C){
			overlay.load(":new/images/C.png");
		}

		result.fill(Qt::transparent); // force alpha channel
		{
		QPainter painter(&result);
		painter.drawPixmap(0, 0, pix);
		painter.drawPixmap(100, 100, overlay);
		}
		return result;
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
