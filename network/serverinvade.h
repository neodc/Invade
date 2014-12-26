#ifndef SERVERINVADE_H
#define SERVERINVADE_H

#include <QDialog>

#include "view/observateur.h"

namespace Ui {
	class ServerInvade;
}

class ServerInvade : public QDialog, public Observateur{
		Q_OBJECT

	public:
		explicit ServerInvade(QWidget *parent = 0);
		~ServerInvade();

	private:
		Ui::ServerInvade *ui;
};

#endif // SERVERINVADE_H
