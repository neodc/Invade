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
		EliteLabel * Soldier;
		EliteLabel * EliteA;
		EliteLabel * EliteB;
		EliteLabel * EliteC;
		QLabel * Arrows;
		QLabel * SoldierValue;
		QLabel * EliteAValue;
		QLabel * EliteBValue;
		QLabel * EliteCValue;

		EffectLabel * noEffect;
		EffectLabel * increasedMovement;
		EffectLabel * incrementSoldier;
		EffectLabel * improvedAttack;
		EffectLabel * changeSoldier;
		QCheckBox * BombShell;

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
