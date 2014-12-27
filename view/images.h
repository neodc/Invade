#ifndef IMAGES_H
#define IMAGES_H
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <map>
#include "../model/unittype.h"
#include "../model/side.h"

class Images
{
	static QImage tile_;
//	static std::map<UnitType, QImage> pawns_;
	static QImage pawn_;
	static std::map<unsigned, QImage> dice_;
	static std::map<unsigned, QImage> effArrows_;

public:
	static QPixmap tile(bool selected = false);
	static QPixmap pawn(UnitType type = UnitType::NORMAL, Side side = Side::NORTH, bool selected = false, bool damaged = false);
	static QPixmap dice(unsigned value, bool selected = false);
	static QPixmap effArrows(unsigned value);
private:
	static QImage changeImage(QImage origin, int dr, int dg, int db);
};

#endif // IMAGES_H
