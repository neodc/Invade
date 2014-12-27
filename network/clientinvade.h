#ifndef CLIENTINVADE_H
#define CLIENTINVADE_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QJsonObject>

#include "view/sujetDObservation.h"
#include "model/invade.h"

class ClientInvade : public QObject, public SujetDObservation{
		Q_OBJECT
	public:
		explicit ClientInvade(QObject *parent = 0);
		void connectToHost(const QString & hostName, quint16 port);

		bool stable() const;
		const Invade & model() const;
	private:
		Invade model_;
		Side side_;

		QTcpSocket connection_;
		bool stable_;
		quint16 blockSize_;

	signals:

	private slots:
		void readyRead();
		void lostConnection();
		void newConnection();

	private:
		bool isOrderValid(QJsonObject json);
		void receiveOrder(QJsonObject json);
		void receiveRefresh(QJsonObject json);
		void receiveError(QJsonObject json);
};

#endif // CLIENTINVADE_H
