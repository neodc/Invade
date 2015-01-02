#ifndef SERVERINVADEUI_H
#define SERVERINVADEUI_H

#include <QDialog>
#include <QTcpServer>
#include <map>
#include <QString>
#include <QJsonObject>

#include "view/observateur.h"
#include "model/invade.h"
#include "model/side.h"
#include "network/serverinvade.h"

namespace Ui {
	class ServerInvade;
}

class ServerInvadeUI : public QDialog {
		Q_OBJECT

	public:
		explicit ServerInvadeUI(int port, QWidget * parent = 0);
		~ServerInvadeUI();

	private:
		Ui::ServerInvade * ui;
		ServerInvade server_;
};

#endif // SERVERINVADEUI_H
