/*!
* \file invadeconnection.h
* \brief Definition of the connection dialog.
*/
#ifndef INVADECONNECTION_H
#define INVADECONNECTION_H

#include <QDialog>

namespace Ui {
	class InvadeConnection;
}

/*!
 * \brief The InvadeConnection class.
 * A QDialog that appears when the program launches.
 */
class InvadeConnection : public QDialog {
		Q_OBJECT

	public:

		/*!
		 * \brief InvadeConnection InvadeConnection with one parameter.
		 * \param parent The parent of the Dialog.
		 */
		explicit InvadeConnection(QWidget * parent = 0);

		/*!
		 * \brief server Tells if the program must start a server or a client.
		 * \return If a server must be started. Otherwise, a client will be started.
		 */
		bool server();

		/*!
		 * \brief host Returns the address of the server host.
		 * \return The server host address.
		 */
		QString host();

		/*!
		 * \brief name Returns the nickname of the client.
		 * \return The nickname of the client.
		 */
		QString name();

		/*!
		 * \brief port Returns the port the server is on.
		 * \return The port the server is on.
		 */
		int port();

		~InvadeConnection();

	private:

		Ui::InvadeConnection * ui;

	private slots:

		void showHost();
};

#endif // INVADECONNECTION_H
