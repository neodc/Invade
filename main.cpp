#include <QApplication>
#include <iostream>

#include "invadeui.h"
#include "model/unittype.h"
#include "model/position.h"
#include "model/unit.h"
#include "model/player.h"

int main(int, char *[]){
	srand (time(NULL));

	Player p("name");

	std::cout << p << std::endl;

/*
	QApplication a(argc, argv);
	InvadeUI w;
	w.show();

	return a.exec();
*/
}
