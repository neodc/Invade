#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include <QString>

typedef struct{
	unsigned x;
	unsigned y;
} Position;

std::ostream & operator<< (std::ostream & out, const Position& in);

QString pos2str(const Position& pos);
Position str2pos(const QString& s);

bool operator<(const Position & first, const Position & second);

bool operator==(const Position & first, const Position & second);
bool operator!=(const Position & first, const Position & second);

#endif // POSITION_H
