#include <QApplication>
#include <iostream>

#include "invadeui.h"
#include "model/unittype.h"

int main(int argc, char *argv[]){

	std::cout << UnitType::NORMAL.pvMax() << std::endl;

/*
	QApplication a(argc, argv);
	InvadeUI w;
	w.show();

	return a.exec();
*/
}
