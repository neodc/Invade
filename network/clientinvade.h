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
		bool requestedNewGame() const;

		void name(const QString & name);
		void endPhase();
		void swapDice(const DiceType d1, const DiceType d2);
		void chooseEffect(Effect effect, UnitType elite = UnitType::NORMAL);
		void move(const Position origin, const Position dest);
		void addUnit(const Position position, const UnitType type);
		void moveCommander(const Position origin, const Position dest);
		void attack(const Position origin, const Position dest, bool bombshell = false);
		void newGame(bool ok = true);

	private:
		Invade model_;
		Side side_;
		bool requestedNewGame_;

		QTcpSocket connection_;
		bool stable_;
		quint16 blockSize_;

	signals:

	private slots:
		void readyRead();
		void lostConnection();
		void newConnection();

	private:
		void sendMessage(QString method, QJsonObject parameters);
		bool isOrderValid(QJsonObject json);
		void receiveOrder(QJsonObject json);
		void receiveRefresh(QJsonObject json);
		void receiveError(QJsonObject json);
		void receiveRequestNewGame(QJsonObject json);
};

#endif // CLIENTINVADE_H
