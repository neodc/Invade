#include <QApplication>
#include <iostream>

#include "view/invadeui.h"
#include "model/unittype.h"
#include "model/position.h"
#include "model/unit.h"
#include "model/player.h"
#include "model/board.h"

#include "network/serverinvade.h"
#include "network/clientinvade.h"

int main(int argc, char *argv[]){
	srand (time(NULL));

	Images::reload();

	Invade * invade;
	invade = new Invade;
	invade->begin("YOLO","SWAG");


	QApplication a(argc, argv);

//	ClientInvade c;
//	c.connectToHost("127.0.0.1", 5423);
	InvadeUI w{invade};
//	ServerInvade w;
	w.show();
	return a.exec();

}
