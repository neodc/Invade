/*!
* \file invadeui.h
* \brief Definition of the invadeui class.
*/
#ifndef INVADEUI_H
#define INVADEUI_H

#include <QMainWindow>
#include <QCheckBox>
#include "view/observateur.h"
#include "view/tilelabel.h"
#include "view/dicelabel.h"
#include "view/unitlabel.h"
#include "view/effectlabel.h"
#include "view/images.h"
#include "network/clientinvade.h"

namespace Ui {
	class InvadeUI;
}

/*!
 * \brief The InvadeUI class.
 * A class used to display the whole game.
 */
class InvadeUI : public QMainWindow, public Observateur {
		Q_OBJECT
		ClientInvade invade_;

		UnitType selectedUnitType = UnitType::NORMAL;
		Position PosTmp{100, 100};
		QLabel nbActions_;
		QLabel warning_;
		DiceLabel * DiceTmp = NULL;
		QLabel results;
		bool showEndPhase = false;

		DiceLabel * COM;
		DiceLabel * ATT;
		DiceLabel * EFF;
		DiceLabel * ABS;
		DiceLabel * ORD;

		QLabel * Arrows;
		QLabel * labelCOM;
		QLabel * labelABS;
		QLabel * labelORD;
		QLabel * labelEFF;
		QLabel * labelATT;

		UnitLabel * Soldier;
		UnitLabel * EliteA;
		UnitLabel * EliteB;
		UnitLabel * EliteC;
		QLabel * SoldierValue;
		QLabel * EliteAValue;
		QLabel * EliteBValue;
		QLabel * EliteCValue;

		DiceLabel * COMenemy;
		DiceLabel * ATTenemy;
		DiceLabel * EFFenemy;
		DiceLabel * ABSenemy;
		DiceLabel * ORDenemy;

		QLabel * ArrowsEnemy;
		QLabel * labelCOMenemy;
		QLabel * labelABSenemy;
		QLabel * labelORDenemy;
		QLabel * labelEFFenemy;
		QLabel * labelATTenemy;

		UnitLabel * SoldierEnemy;
		UnitLabel * EliteAEnemy;
		UnitLabel * EliteBEnemy;
		UnitLabel * EliteCEnemy;
		QLabel * SoldierValueEnemy;
		QLabel * EliteAValueEnemy;
		QLabel * EliteBValueEnemy;
		QLabel * EliteCValueEnemy;

		EffectLabel * noEffect;
		EffectLabel * increasedMovement;
		EffectLabel * incrementSoldier;
		EffectLabel * improvedAttack;
		EffectLabel * changeSoldier;

	public:

		/*!
		 * \brief InvadeUI InvadeUI constructor with four parameters.
		 * \param name The nickname of the client.
		 * \param host The server host address.
		 * \param port The port the server is on.
		 * \param parent The parent of the Window.
		 */
		explicit InvadeUI(QString name, QString host, int port, QWidget * parent = 0);

		/*!
		 * \brief rafraichir Refreshes the UI.
		 */
		void rafraichir(SujetDObservation *);

		~InvadeUI() noexcept;

	private:

		Ui::InvadeUI * ui;
		void move(Position sender);
		void moveCommander(Position sender);
		void attack(Position sender, bool bombshell = false);
		void rightAttack(Position sender);
		void refreshStat();

	private slots:

		void nextPhase();
		void swapDice();
		void chooseEffect();
		void unitAction();
		void rightUnitAction();
		void begin();
		void selectUnit();
		void quit();
};

#endif // INVADEUI_H
