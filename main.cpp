#include "invadeui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	InvadeUI w;
	w.show();

	return a.exec();
}
