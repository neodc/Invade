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
		explicit ServerInvade(Invade * model, QWidget *parent = 0);
		~ServerInvade();
		void rafraichir(SujetDObservation *);

	private:
		Ui::ServerInvade *ui;
		Invade * model;
		QTcpServer *tcpServer;

		std::map<Side, QTcpSocket*> clients;
		quint16 blockSize;

	private slots:
		void newConnection();
		void lostConnection();
		void readyRead();

	private:
		void sendMessage(QString method, QJsonObject parameters, QTcpSocket *client);
		void sendError(QString reason, QTcpSocket *client);
		bool isOrderValid(QJsonObject json);
		void receveOrder(QJsonObject json, Side side);
};

#endif // SERVERINVADE_H
