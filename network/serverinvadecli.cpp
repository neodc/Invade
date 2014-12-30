#include "serverinvadecli.h"

#include <QDebug>

ServerInvadeCLI::ServerInvadeCLI(int port, QObject *parent) :
	QObject(parent),
	server_{port, this}{

	if (!server_.isListening()) {
		qDebug() << tr("Unable to start the server: %1.").arg(server_.errorString());
		return;
	}

	qDebug() << tr("The server is running on port %1").arg(server_.serverPort());
}
