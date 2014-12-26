#include <QApplication>
#include <iostream>

#include "invadeui.h"
#include "model/unittype.h"
#include "model/position.h"
#include "model/unit.h"
#include "model/player.h"
#include "model/board.h"

int main(int argc, char *argv[]){
	srand (time(NULL));

	/*Board b;

	Unit u{UnitType::NORMAL, Side::NORTH};

	b.addUnit({0,0}, u);
	b.addUnit({1,0}, u);
	b.addUnit({0,1}, u);
	b.addUnit({1,1}, u);

	b.unitAt({0,0}).disable();

	b.reset();

	std::cout << b << std::endl;*/

	Invade * invade;
	invade = new Invade;
	invade->begin("YOLO","SWAG");


	QApplication a(argc, argv);
	InvadeUI w{invade};
	w.show();

	return a.exec();

}
