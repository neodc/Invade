#ifndef INVADEUI_H
#define INVADEUI_H

#include <QMainWindow>
#include "view/observateur.h"
#include "model/invade.h"

namespace Ui {
	class InvadeUI;
}

class InvadeUI : public QMainWindow, public Observateur{
	Q_OBJECT
	Invade *invade_;

	public:
		explicit InvadeUI(Invade * invade, QWidget *parent = 0);
		void rafraichir(SujetDObservation *);
		~InvadeUI() noexcept;

	private:
		Ui::InvadeUI *ui;
	private slots:
		void nextPhase();
		void swapDice();
		void choseEffect();
		void move();
		void moveCommender();
		void attack();
		void newGame();
		void quit();
};

#endif // INVADEUI_H
