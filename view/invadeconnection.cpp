#include "invadeconnection.h"
#include "ui_invadeconnection.h"

InvadeConnection::InvadeConnection(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InvadeConnection){
	ui->setupUi(this);

	connect( ui->server, &QCheckBox::stateChanged, this,  &InvadeConnection::showHost);
}

InvadeConnection::~InvadeConnection(){
	delete ui;
}

bool InvadeConnection::server(){
	return ui->server->isChecked();
}

QString InvadeConnection::host(){
	return ui->host->text();
}

int InvadeConnection::port(){
	return ui->port->value();
}

void InvadeConnection::showHost(){
	ui->host->setEnabled( !ui->server->isChecked() );
}
