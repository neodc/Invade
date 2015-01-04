/*!
 * \file clientinvade.h
 * \brief Definition of the ClientInvade class.
 */
#ifndef CLIENTINVADE_H
#define CLIENTINVADE_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QJsonObject>

#include "view/sujetDObservation.h"
#include "model/invade.h"

/*!
 * \brief Manage a connection to a ServerInvade and give acces to the state of the game.
 */
class ClientInvade : public QObject, public SujetDObservation {
		Q_OBJECT
	public:
		/*!
		 * \brief Construct a new instance of ClientInvade.
		 * \param parent The parent of the object.
		 */
		explicit ClientInvade(QObject * parent = 0);
		/*!
		 * \brief Connect to a server.
		 * \param hostName The hostname of the server.
		 * \param port The port of the server.
		 */
		void connectToHost(const QString & hostName, quint16 port);

		/*!
		 * \brief Return if the connection is stable (if it is connected to a server).
		 * \return If the connection is stable.
		 */
		bool stable() const;
		/*!
		 * \brief Return the current state of the game.
		 * \return The current state of the game.
		 */
		const Invade & model() const;
		/*!
		 * \brief Return if a new game has been requested.
		 * \return If a new game has been requested.
		 */
		bool requestedNewGame() const;
		/*!
		 * \brief Return the side played by this connection.
		 * \return The side played by this connection.
		 */
		Side side() const;

		/*!
		 * \brief Send the order to choose a name (can only be use if the game state is NO_PLAYER.
		 * \param name The name.
		 */
		void name(const QString & name);
		/*!
		 * \brief End the phase.
		 */
		void endPhase();
		/*!
		 * \brief Swaps two dices.
		 * \param d1 The first dice.
		 * \param d2 The second dice.
		 */
		void swapDice(const DiceType d1, const DiceType d2);
		/*!
		 * \brief Choose an effect to apply.
		 * \param effect The chosen effect
		 * \param elite The elite needed by certains effects.
		 */
		void chooseEffect(Effect effect, UnitType elite = UnitType::NORMAL);
		/*!
		 * \brief Moves a unit.
		 * \param origin the original position of the unit.
		 * \param dest the destination of the unit.
		 */
		void move(const Position origin, const Position dest);
		/*!
		 * \brief Add a unit in the board.
		 * \param position the position where we want to add the unit
		 * \param type the unit.
		 */
		void addUnit(const Position position, const UnitType type);
		/*!
		 * \brief Moves the unit moved by the commander.
		 * \param origin the original position of the unit.
		 * \param dest the destination of the unit.
		 */
		void moveCommander(const Position origin, const Position dest);
		/*!
		 * \brief Effectuate the attack.
		 * \param origin The position of the attacking unit.
		 * \param dest Attacked unit.
		 * \param bombshell Tells if the attack use a bombshell or not
		 */
		void attack(const Position origin, const Position dest, bool bombshell = false);
		/*!
		 * \brief Send the order to make a new game (if no newgame has been ask and ok is true a new game will be ask to the other client, if a newgame has been ask and ok is true a new game will start and if a newgame has been ask and ok is false the request will be cancel).
		 * \param ok If it accept the new game.
		 */
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
		void readOrder(QTcpSocket * clientConnection);
		void sendMessage(QString method, QJsonObject parameters);
		bool isOrderValid(QJsonObject json);
		void receiveOrder(QJsonObject json);
		void receiveRefresh(QJsonObject json);
		void receiveError(QJsonObject json);
		void receiveRequestNewGame(QJsonObject json);
};

#endif // CLIENTINVADE_H
