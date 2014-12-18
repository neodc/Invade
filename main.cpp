#include <QApplication>
#include <iostream>

#include "invadeui.h"
#include "model/unittype.h"
#include "model/position.h"
#include "model/unit.h"

int main(int, char *[]){

	Unit u(UnitType::NORMAL, Side::NORTH);

	std::cout << u << std::endl;
/*
	QApplication a(argc, argv);
	InvadeUI w;
	w.show();

	return a.exec();
*/
}
