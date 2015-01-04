/*!
 * \file serverinvadecli.h
 * \brief Definition of the ServerInvadeCLI class.
 */
#ifndef SERVERINVADECLI_H
#define SERVERINVADECLI_H

#include <QObject>
#include "network/serverinvade.h"

/*!
 * \brief Command line view of the server.
 */
class ServerInvadeCLI : public QObject {
		Q_OBJECT
	public:
		/*!
		 * \brief Construct a new instance of ServerInvadeCLI.
		 * \param port The port to listen to.
		 * \param parent The parent of the object.
		 */
		explicit ServerInvadeCLI(int port, QObject * parent = 0);

	private:
		ServerInvade server_;

};

#endif // SERVERINVADECLI_H
