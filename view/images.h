#ifndef IMAGES_H
#define IMAGES_H
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <map>
#include "../model/unit.h"
#include "../model/side.h"

class Images
{
	static QImage tile_;
//	static std::map<UnitType, QImage> pawns_;
	static QImage pawn_;
	static QImage A_;
	static QImage B_;
	static QImage Bbomb_;
	static QImage C_;
	static std::map<unsigned, QImage> dice_;
	static std::map<unsigned, QImage> effArrows_;

public:
	static QPixmap tile(bool selected = false);
	static QPixmap pawn(UnitType type = UnitType::NORMAL, bool selected = false, Side side = Side::NORTH);
	static QPixmap pawn(Unit unit, bool selected = false);
	static QPixmap dice(unsigned value, bool selected = false);
	static QPixmap effArrows(unsigned value);
private:
	static QImage changeImage(QImage origin, int dr, int dg, int db);
};

#endif // IMAGES_H
