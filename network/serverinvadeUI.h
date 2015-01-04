/*!
 * \file serverinvadeUI.h
 * \brief Definition of the ServerInvadeUI class.
 */
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
	class ServerInvadeUI;
}

/*!
 * \brief Graphic view of the server.
 */
class ServerInvadeUI : public QDialog {
		Q_OBJECT

	public:
		/*!
		 * \brief Construct a new instance of ServerInvadeUI.
		 * \param port The port to listen to.
		 * \param parent The parent of the object.
		 */
		explicit ServerInvadeUI(int port, QWidget * parent = 0);
		~ServerInvadeUI();

	private:
		Ui::ServerInvadeUI * ui;
		ServerInvade server_;
};

#endif // SERVERINVADEUI_H
