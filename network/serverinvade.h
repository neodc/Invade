#ifndef SERVERINVADE_H
#define SERVERINVADE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include "view/observateur.h"
#include "model/invade.h"

class ServerInvade : public QObject, public Observateur{
		Q_OBJECT
	public:
		explicit ServerInvade(int port, QObject *parent);

		void rafraichir(SujetDObservation *);
		bool isListening() const;
		QString errorString() const;
		int serverPort() const;

	private:
		Invade model_;
		QTcpServer *tcpServer_;

		std::map<Side, QTcpSocket*> clients_;
		std::map<Side, std::string> names_;
		std::map<Side, bool> requestNewGame_;
		quint16 blockSize_;

	signals:

	private slots:
		void newConnection();
		void lostConnection();
		void readyRead();

	private:
		void sendMessage(QString method, QJsonObject parameters, QTcpSocket *client);
		void sendError(QString reason, QTcpSocket *client);
		void sendRequestNewGame(QTcpSocket *client);
		void readOrder(QTcpSocket *clientConnection);
		bool isOrderValid(QJsonObject json);
		void receiveOrder(QJsonObject json, Side side);
};

#endif // SERVERINVADE_H
