#ifndef SERVERINVADE_H
#define SERVERINVADE_H

#include <QDialog>
#include <QTcpServer>
#include <map>
#include <QString>
#include <QJsonObject>

#include "view/observateur.h"
#include "model/invade.h"
#include "model/side.h"

namespace Ui {
	class ServerInvade;
}

class ServerInvade : public QDialog, public Observateur{
		Q_OBJECT

	public:
		explicit ServerInvade(int port, QWidget *parent = 0);
		~ServerInvade();
		void rafraichir(SujetDObservation *);

	private:
		Ui::ServerInvade *ui;
		Invade model_;
		QTcpServer *tcpServer_;

		std::map<Side, QTcpSocket*> clients_;
		std::map<Side, std::string> names_;
		quint16 blockSize_;

	private slots:
		void newConnection();
		void lostConnection();
		void readyRead();

	private:
		void sendMessage(QString method, QJsonObject parameters, QTcpSocket *client);
		void sendError(QString reason, QTcpSocket *client);
		bool isOrderValid(QJsonObject json);
		void receiveOrder(QJsonObject json, Side side);
};

#endif // SERVERINVADE_H
