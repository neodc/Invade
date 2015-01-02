#include <QApplication>
#include <iostream>
#include <sstream>
#include <QDebug>

#include "view/invadeui.h"
#include "view/invadeconnection.h"

#include "model/unittype.h"
#include "model/position.h"
#include "model/unit.h"
#include "model/player.h"
#include "model/board.h"

#include "network/serverinvadeUI.h"
#include "network/serverinvadecli.h"
#include "network/clientinvade.h"

int main(int argc, char *argv[]){
	srand(time(NULL));

	Images::reload();

	if( argc >= 2 ){
		QCoreApplication a(argc, argv);

		std::istringstream ss(argv[1]);
		int port;
		if (!(ss >> port)){
			qDebug() << "Invalide port";
			return 1;
		}

		ServerInvadeCLI cli{port};

		return a.exec();
	}else{
		QApplication a(argc, argv);
		QWidget * w;

		InvadeConnection c;
		if( c.exec() == QDialog::Rejected ) return 0;

		if( c.server() ){
			w = new ServerInvadeUI{ c.port() };
		}else{
			w = new InvadeUI{ c.name(), c.host(), c.port() };
		}
		w->show();

		return a.exec();
	}
}
