#include "serverinvade.h"
#include "ui_serverinvade.h"

ServerInvade::ServerInvade(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ServerInvade)
{
	ui->setupUi(this);
}

ServerInvade::~ServerInvade(){
	delete ui;
}
