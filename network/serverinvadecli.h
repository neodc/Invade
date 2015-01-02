#ifndef SERVERINVADECLI_H
#define SERVERINVADECLI_H

#include <QObject>
#include "network/serverinvade.h"

class ServerInvadeCLI : public QObject {
		Q_OBJECT
	public:
		explicit ServerInvadeCLI(int port, QObject * parent = 0);

	private:
		ServerInvade server_;

};

#endif // SERVERINVADECLI_H
