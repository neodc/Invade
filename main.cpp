#include <QApplication>
#include <iostream>

#include "view/invadeui.h"
#include "view/invadeconnection.h"

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

	InvadeConnection c;
	if( c.exec() == QDialog::Rejected ) return 0;

	QWidget * w;

	if( c.server() ){
		w = new ServerInvade{ c.port() };
	}else{
		w = new InvadeUI{invade};
	}
	w->show();

//	ClientInvade c;
//	c.connectToHost("127.0.0.1", 5423);

	return a.exec();

}
