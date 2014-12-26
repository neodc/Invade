#ifndef INVADEUI_H
#define INVADEUI_H

#include <QMainWindow>
#include "view/observateur.h"

namespace Ui {
	class InvadeUI;
}

class InvadeUI : public QMainWindow, public Observateur{
		Q_OBJECT

	public:
		explicit InvadeUI(QWidget *parent = 0);
		void rafraichir(SujetDObservation *);
		~InvadeUI() noexcept;

	private:
		Ui::InvadeUI *ui;
};

#endif // INVADEUI_H
