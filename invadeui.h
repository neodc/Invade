#ifndef INVADEUI_H
#define INVADEUI_H

#include <QMainWindow>

namespace Ui {
	class InvadeUI;
}

class InvadeUI : public QMainWindow
{
		Q_OBJECT

	public:
		explicit InvadeUI(QWidget *parent = 0);
		~InvadeUI();

	private:
		Ui::InvadeUI *ui;
};

#endif // INVADEUI_H
