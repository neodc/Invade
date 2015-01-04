/*!
 * \file serverinvade.h
 * \brief Definition of the ServerInvade class.
 */
#ifndef SERVERINVADE_H
#define SERVERINVADE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include "view/observateur.h"
#include "model/invade.h"

/*!
 * \brief Manage the connection to the 2 client.
 */
class ServerInvade : public QObject, public Observateur {
		Q_OBJECT
	public:
		/*!
		 * \brief Construct a new instance of ServerInvade.
		 * \param port The port to listen to.
		 * \param parent The parent of the object.
		 */
		explicit ServerInvade(int port, QObject * parent);

		/*!
		 * \brief Update the state of the client.
		 */
		void rafraichir(SujetDObservation *);
		/*!
		 * \brief Return if the server is listening to new connection.
		 * \return If the server is listening to new connection.
		 */
		bool isListening() const;
		/*!
		 * \brief Return the message of the last error.
		 * \return The message of the last error.
		 */
		QString errorString() const;
		/*!
		 * \brief Return the port the server is listening to.
		 * \return The port the server is listening to.
		 */
		int serverPort() const;

	private:
		Invade model_;
		QTcpServer * tcpServer_;

		std::map<Side, QTcpSocket *> clients_;
		std::map<Side, std::string> names_;
		std::map<Side, bool> requestNewGame_;
		quint16 blockSize_;

	signals:

	private slots:
		void newConnection();
		void lostConnection();
		void readyRead();

	private:
		void sendMessage(QString method, QJsonObject parameters, QTcpSocket * client);
		void sendError(QString reason, QTcpSocket * client);
		void sendRequestNewGame(QTcpSocket * client);
		void readOrder(QTcpSocket * clientConnection);
		bool isOrderValid(QJsonObject json);
		void receiveOrder(QJsonObject json, Side side);
};

#endif // SERVERINVADE_H
