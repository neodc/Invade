#include "position.h"

#include <QStringList>

std::ostream & operator<< ( std::ostream & out, const Position & in) {
	out << '{' << in.x << ',' << in.y << '}';
	return out;
}

QString pos2str(const Position & pos) {
	return QString("%1:%2").arg(pos.x).arg(pos.y);
}

Position str2pos(const QString & s) {
	Position ret;

	QStringList list{s.split(':')};

	ret.x = list[0].toUInt();
	ret.y = list[1].toUInt();

	return ret;
}

bool operator<(const Position & first, const Position & second) {
	return (first.y < second.y) || (first.y == second.y && first.x < second.x);
}

bool operator==(const Position & first, const Position & second) {
	return (first.y == second.y) && (first.x == second.x);
}

bool operator!=(const Position & first, const Position & second) {
	return !(first == second);
}
