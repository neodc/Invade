#ifndef INVADEUI_H
#define INVADEUI_H

#include <QMainWindow>
#include <QCheckBox>
#include "view/observateur.h"
#include "view/tilelabel.h"
#include "view/dicelabel.h"
#include "view/elitelabel.h"
#include "view/effectlabel.h"
#include "view/images.h"
//#include "model/invade.h"
#include "network/clientinvade.h"

namespace Ui {
	class InvadeUI;
}

class InvadeUI : public QMainWindow, public Observateur{
		Q_OBJECT
//		Invade *invade_;
		ClientInvade invade_;

		UnitType selectedUnitType = UnitType::NORMAL;
		Position PosTmp{100,100};
		QLabel nbActions_;
		DiceLabel * DiceTmp = NULL;

		DiceLabel * COM;
		DiceLabel * ATT;
		DiceLabel * EFF;
		DiceLabel * ABS;
		DiceLabel * ORD;
		DiceLabel * DEF;
		QLabel * Arrows;
		QLabel * labelCOM;
		QLabel * labelABS;
		QLabel * labelORD;
		QLabel * labelEFF;
		QLabel * labelATT;
		QLabel * labelDEF;

		EliteLabel * Soldier;
		EliteLabel * EliteA;
		EliteLabel * EliteB;
		EliteLabel * EliteC;
		QLabel * SoldierValue;
		QLabel * EliteAValue;
		QLabel * EliteBValue;
		QLabel * EliteCValue;

		DiceLabel * COMenemy;
		DiceLabel * ATTenemy;
		DiceLabel * EFFenemy;
		DiceLabel * ABSenemy;
		DiceLabel * ORDenemy;
		DiceLabel * DEFenemy;
		QLabel * ArrowsEnemy;
		QLabel * labelCOMenemy;
		QLabel * labelABSenemy;
		QLabel * labelORDenemy;
		QLabel * labelEFFenemy;
		QLabel * labelATTenemy;
		QLabel * labelDEFenemy;

		EliteLabel * SoldierEnemy;
		EliteLabel * EliteAEnemy;
		EliteLabel * EliteBEnemy;
		EliteLabel * EliteCEnemy;
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
		explicit InvadeUI(QString name, QString host, int port, QWidget *parent = 0);
		void rafraichir(SujetDObservation *);
		~InvadeUI() noexcept;

private:
		Ui::InvadeUI *ui;
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
