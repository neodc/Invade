#ifndef INVADECONNECTION_H
#define INVADECONNECTION_H

#include <QDialog>

namespace Ui {
	class InvadeConnection;
}

class InvadeConnection : public QDialog{
		Q_OBJECT

	public:
		explicit InvadeConnection(QWidget *parent = 0);
		~InvadeConnection();

		bool server();
		QString host();
		int port();

	private:
		Ui::InvadeConnection *ui;

	private slots:
		void showHost();
};

#endif // INVADECONNECTION_H
